#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

class MedianFinder {
    priority_queue<int> lo;                              // max heap
    priority_queue<int, vector<int>, greater<int> > hi;   // min heap

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        lo.push(num);                                    // Add to max heap

        hi.push(lo.top());                               // balancing step
        lo.pop();

        if (lo.size() < hi.size()) {                     // maintain size property
            lo.push(hi.top());
            hi.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        return lo.size() > hi.size() ? (double) lo.top() : (lo.top() + hi.top()) * 0.5;
    }
};

bool scan_dir(char* dir, vector<string> &files)
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

int main()
{
    vector<string> files;
    char dir[] = "./data40M";
    scan_dir(dir, files);

    MedianFinder mf;
    clock_t start = clock();
    for (int i=0; i<files.size(); i++)
    {
        cout<<"loading "<<files[i]<<endl;
        ifstream fin;
        fin.open(files[i].c_str(),ios::in);
        char buff[256];
        while(fin.getline(buff,256))
        {
            int n = atoi(buff);
            mf.addNum(n);
        }
    }
    clock_t end = clock();
    cout<<"Median: "<<mf.findMedian()<<endl;
    cout<<"Time consume: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;

    return 0;
}
