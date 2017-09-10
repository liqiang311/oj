#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

bool scan_dir(const char* dir, vector<string> &files)
{
    DIR *dp;                                            // 定义子目录流指针  
    struct dirent *entry;                               // 定义dirent结构指针保存后续目录  
    struct stat statbuf;                                // 定义statbuf结构保存文件属性  
    if((dp = opendir(dir)) == NULL) return false;       // 打开目录，获取子目录流指针，判断操作是否成功  
    chdir (dir);                                        // 切换到当前目录  
    while((entry = readdir(dp)) != NULL)                // 获取下一级目录信息，如果未否则循环  
    {
        lstat(entry->d_name, &statbuf);                 // 获取下一级成员属性  
        if(S_IFDIR &statbuf.st_mode)                    // 判断下一级成员是否是目录  
        {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
              continue;

            if (!scan_dir(entry->d_name, files)) return false;              // 递归调用自身，扫描下一级目录的内容  
        }
        else
        {
            files.push_back(string(getcwd(NULL, 0)) + "/" + string(entry->d_name));
        }
    }
    chdir("..");                                                  // 回到上级目录  
    closedir(dp);                                                 // 关闭子目录流  
    return true;
}

void read_data(vector<string> &files, vector<int> &data)
{
    char buff[256];
    for (int i=0; i<files.size(); i++)
    {
        ifstream fin(files[i].c_str(),ios::in);
        if (!fin.is_open())
        {
            cout<<"load "<<files[i]<<" fail."<<endl;
            continue;
        }
        else cout<<"loading "<<files[i]<<endl;
        while(fin.getline(buff,256))
            data.push_back(atoi(buff));
        fin.close();
    }
}

static void HandleError( cudaError_t err, const char *file, int line ) 
{
    if (err != cudaSuccess) 
    {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ), file, line );
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

// a>=b return 0   a<b return 1
__device__ int cmp_without_if(int a, int b)
{
    int c = a - b;
    return (c >> 31) & 0x1;
}

__device__ int max_without_if(int a, int b)
{
    int c = a - b;
    int k = (c >> 31) & 0x1;
    return a - k * c;
}

__device__ int min_without_if(int a, int b)
{
    return (a + b) - max_without_if(a,b);
}

__global__ void reduce_sum(int *d_arr, int len, int *d_sum)
{
    __shared__ int cache[1024];
    int tid = threadIdx.x;

    cache[tid] = 0;
    for(int i=tid; i<len; i+=blockDim.x)
        cache[tid] += d_arr[i];
    __syncthreads();

    int i = blockDim.x/2;
    while(i)
    {
        if (tid < i) cache[tid] += cache[tid+i];
        __syncthreads();
        i /= 2;
    }
    if (tid == 0) *d_sum = cache[0];
}

__global__ void reduce_min_max(int *d_min_arr, int *d_max_arr, int len, int *d_min, int *d_max)
{
    __shared__ int mincache[1024];
    __shared__ int maxcache[1024];
    int tid = threadIdx.x;
    mincache[tid] = INT_MAX/2;
    maxcache[tid] = INT_MIN/2;

    for(int i=tid; i<len; i+=blockDim.x)
    {
        mincache[tid] = min_without_if(mincache[tid], d_min_arr[i]);
        maxcache[tid] = max_without_if(maxcache[tid], d_max_arr[i]); 
    }
    __syncthreads();

    int i = blockDim.x/2;
    while(i)
    {
        if (tid < i)
        {
            mincache[tid] = min_without_if(mincache[tid], mincache[tid+i]);
            maxcache[tid] = max_without_if(maxcache[tid], maxcache[tid+i]); 
        }
        __syncthreads();
        i /= 2;
    }
    if (tid == 0)
    {
        *d_min = mincache[0];
        *d_max = maxcache[0];
    }
}

__global__ void partition_min_max(int *d_arr, int *d_flag, int len, int *d_min_arr, int *d_max_arr)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int max = INT_MIN/2, min = INT_MAX/2;
    for (int i=tid; i<len; i+=blockDim.x*gridDim.x)
    {
        min = d_flag[i] * min_without_if(min, d_arr[i]) + (1 - d_flag[i]) * min;
        max = d_flag[i] * max_without_if(max, d_arr[i]) + (1 - d_flag[i]) * max;
    }
    d_min_arr[tid] = min;
    d_max_arr[tid] = max;
}

__global__ void partition_pivot(int *d_arr, int *d_flag, int len, int *d_pivot_arr)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    d_pivot_arr[tid] = INT_MAX/2;
    for (int i=tid; i<len; i+=blockDim.x*gridDim.x)
    {
        if (d_flag[i])
        {
            d_pivot_arr[tid] = d_arr[i];
            return;
        }
    }
}

__global__ void partition_less_num(int pivot, int *d_arr, int *d_flag, int len, int *d_lt_num_arr)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    d_lt_num_arr[tid] = 0;
    for (int i=tid; i<len; i+=blockDim.x*gridDim.x)
    {
        d_lt_num_arr[tid] += d_flag[i] * cmp_without_if(d_arr[i], pivot);
    }
}

__global__ void partition_remove_less(int pivot,int *d_arr,int *d_flag,int len)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    for (int i=tid; i<len; i+=blockDim.x*gridDim.x)
    {
        d_flag[i] = d_flag[i] * (1 - cmp_without_if(d_arr[i], pivot));
    }
}

__global__ void partition_remove_great(int pivot, int *d_arr, int *d_flag, int len)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    for (int i=tid; i<len; i+=blockDim.x*gridDim.x)
    {
        d_flag[i] = d_flag[i] * cmp_without_if(d_arr[i], pivot);
    }
}

__host__ int nth_order_stat(int target_order_stat, int *h_arr, int *d_arr, int *d_flag, int len);

__host__ int partition_on_pivot(int target_order_stat, int *h_arr, int *d_arr, int *d_flag, int len, int pivot_index)
{
    int threadNum = 1024;
    int blockNum = (len + threadNum - 1) / threadNum;
    blockNum = blockNum <= 1024 ? blockNum : 1024;

    static int pivot_arr[1024];
    int pivot;
    if (pivot_index == 0)
    {
        int *d_pivot_arr;
        HANDLE_ERROR( cudaMalloc((void**)&d_pivot_arr,sizeof(int)*1024) );
        partition_pivot<<<1,1024>>>(d_arr,d_flag,len,d_pivot_arr);
        HANDLE_ERROR( cudaMemcpy(&pivot_arr,d_pivot_arr,sizeof(int)*1024,cudaMemcpyDeviceToHost) );
        HANDLE_ERROR( cudaFree(d_pivot_arr) );
        pivot = pivot_arr[0];
    }
    else
        pivot = pivot_arr[rand()%1024];

    int *d_lt_num_arr, *d_lt_num, lt_num;
    HANDLE_ERROR( cudaMalloc((void**)&d_lt_num_arr,sizeof(int)*blockNum*threadNum) );
    HANDLE_ERROR( cudaMalloc((void**)&d_lt_num,sizeof(int)) );

    partition_less_num<<<blockNum,threadNum>>>(pivot,d_arr,d_flag,len,d_lt_num_arr);
    reduce_sum<<<1,1024>>>(d_lt_num_arr,blockNum*threadNum,d_lt_num);
    HANDLE_ERROR( cudaMemcpy(&lt_num,d_lt_num,sizeof(int),cudaMemcpyDeviceToHost) );

    HANDLE_ERROR( cudaFree(d_lt_num_arr) );
    HANDLE_ERROR( cudaFree(d_lt_num) );

    int pivot_order_stat = lt_num + 1;
    
    if (pivot_order_stat == target_order_stat) 
        return pivot;
    else if (pivot_order_stat == 1)
        return partition_on_pivot(target_order_stat, h_arr, d_arr, d_flag, len, pivot_index+1);
    else if (pivot_order_stat < target_order_stat)
    {
        target_order_stat -= lt_num;
        partition_remove_less<<<blockNum,threadNum>>>(pivot,d_arr,d_flag,len);
        return nth_order_stat(target_order_stat, h_arr, d_arr, d_flag, len);
    }
    else
    {
        partition_remove_great<<<blockNum,threadNum>>>(pivot,d_arr,d_flag,len);
        return nth_order_stat(target_order_stat, h_arr, d_arr, d_flag, len);
    }
}

__host__ int nth_order_stat(int target_order_stat, int *h_arr, int *d_arr, int *d_flag, int len)
{
    int threadNum = 1024;
    int blockNum = (len + threadNum - 1) / threadNum;
    blockNum = blockNum <= 1024 ? blockNum : 1024;

    int *d_min_arr, *d_max_arr;
    int h_min, h_max, *d_min, *d_max;
    HANDLE_ERROR( cudaMalloc((void**)&d_min_arr,sizeof(int)*blockNum*threadNum) );
    HANDLE_ERROR( cudaMalloc((void**)&d_max_arr,sizeof(int)*blockNum*threadNum) );  
    HANDLE_ERROR( cudaMalloc((void**)&d_min,sizeof(int)) );  
    HANDLE_ERROR( cudaMalloc((void**)&d_max,sizeof(int)) );  

    partition_min_max<<<blockNum,threadNum>>>(d_arr,d_flag,len,d_min_arr,d_max_arr);
    reduce_min_max<<<1,1024>>>(d_min_arr,d_max_arr,blockNum*threadNum,d_min,d_max);
    HANDLE_ERROR( cudaMemcpy(&h_min,d_min,sizeof(int),cudaMemcpyDeviceToHost) );
    HANDLE_ERROR( cudaMemcpy(&h_max,d_max,sizeof(int),cudaMemcpyDeviceToHost) );

    HANDLE_ERROR (cudaFree(d_min_arr));
    HANDLE_ERROR (cudaFree(d_max_arr));
    HANDLE_ERROR (cudaFree(d_min));
    HANDLE_ERROR (cudaFree(d_max));

    if (h_max == h_min || target_order_stat == 1)
        return h_min;
    else if (target_order_stat == len)
        return h_max;
    else
        return partition_on_pivot(target_order_stat, h_arr, d_arr, d_flag, len, 0);
}

__host__ int median(int *arr, int len)
{
    int *d_arr;
    cudaMalloc((void**)&d_arr,sizeof(int)*len);
    cudaMemcpy(d_arr,arr,sizeof(int)*len,cudaMemcpyHostToDevice);

    int *h_flag = new int[len];
    for (int i=0; i<len; i++) h_flag[i] = 1;

    int *d_flag;
    cudaMalloc((void**)&d_flag,sizeof(int)*len);
    cudaMemcpy(d_flag,h_flag,sizeof(int)*len,cudaMemcpyHostToDevice);
    delete[] h_flag;

    int res = nth_order_stat((int)((len+0.5)/2), arr, d_arr, d_flag, len);
    
    cudaFree(d_arr);
    cudaFree(d_flag);
    return res;
}

int main()
{
    //开始时间戳
    clock_t h_t1 = clock();

    //读入数据
    vector<string> files;
    scan_dir("./data40M", files);
    vector<int> h_vec; 
    read_data(files,h_vec);

    //读取数据时间戳
    clock_t h_t2 = clock();

    //GPU运算开始时间
    cudaEvent_t     d_start, d_stop;
    cudaEventCreate( &d_start );
    cudaEventCreate( &d_stop );
    cudaEventRecord( d_start, 0 );

    //调用算法
    int res = median(h_vec.data(), h_vec.size());

    //GPU运算结束时间
    cudaEventRecord( d_stop, 0 );
    cudaEventSynchronize( d_stop );
    float   elapsedTime;
    cudaEventElapsedTime( &elapsedTime, d_start, d_stop );
    printf( "Time on GPU:  %.3f s\n", elapsedTime/1000 );

    //结束时间戳
    clock_t h_end = clock();
    cout<<"Median: "<<res<<endl;
    cout<<"IO Time: "<<(double)(h_t2-h_t1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Algorithm Time: "<<(double)(h_end-h_t2)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Total Time: "<<(double)(h_end-h_t1)/CLOCKS_PER_SEC<<"s"<<endl;

    cudaEventDestroy( d_start );
    cudaEventDestroy( d_stop );
    return 0;
}
