#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
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

int nth_order_stat(int target_order_stat, int *arr, int len);

int partition_on_pivot(int target_order_stat, int *arr, int len)
{
    int pivot = arr[rand()%len];

    int *gt_arr = new int[len];
    int gt_num = 0;
    int *lt_arr = new int[len];
    int lt_num = 0;

    for (int i=0; i<len; i++)
    {
        if (arr[i] < pivot) lt_arr[lt_num++] = arr[i];
        else gt_arr[gt_num++] = arr[i];
    }
    int pivot_order_stat = lt_num + 1;

    if (pivot_order_stat == target_order_stat) 
    {
        delete gt_arr, lt_arr;
        return pivot;
    }
    else if (pivot_order_stat == 1)//没有比pivot更小的数字了
    {
        delete gt_arr, lt_arr;
        return nth_order_stat(target_order_stat, arr, len);
    }
    else if (pivot_order_stat < target_order_stat)//比pivot小的数字可以丢弃
    {
        target_order_stat -= lt_num;
        int res = nth_order_stat(target_order_stat, gt_arr, gt_num);
        delete gt_arr, lt_arr;
        return res;
    }
    else//比pivot大的数字丢弃
    {
        int res = nth_order_stat(target_order_stat, lt_arr, lt_num);
        delete gt_arr, lt_arr;
        return res;
    }
}

int nth_order_stat(int target_order_stat, int *arr, int len)
{
    int max = *(max_element(arr, arr+len));
    int min = *(min_element(arr, arr+len));
    if (max == min || target_order_stat == 1)
        return min;
    else if (target_order_stat == len)
        return max;
    else
        return partition_on_pivot(target_order_stat, arr, len);
}

int median(int *arr, int len)
{
    return nth_order_stat((int)((len+0.5)/2), arr, len);
}



int main()
{
    clock_t start1 = clock();

    vector<string> files;
    scan_dir("./data40M", files);
    vector<int> vec; 
    read_data(files,vec);
    
    clock_t start2 = clock();
    
    int res = median(vec.data(), vec.size());

    clock_t end = clock();

    cout<<"Median: "<<res<<endl;
    cout<<"Read IO time consume: "<<(double)(start2-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Alrogithm time consume: "<<(double)(end-start2)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Total time consume: "<<(double)(end-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}
