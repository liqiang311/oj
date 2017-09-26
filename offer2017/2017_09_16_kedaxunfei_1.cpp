#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string str;
    cin>>str;

    //去掉明显的
    while(1)
    {
        bool isBreak = true;
        for (int i=0; i<str.size()-1; i++)
        {
            if (str.substr(i,2).compare("RL") == 0)
            {
                if (i > 0 && str[i-1] == 'R')
                {
                    str.erase(i,1);
                    i -=2;
                    isBreak = false;
                }
                else if (str[i+2] == 'L')
                {
                    str.erase(i+1,1);
                    i --;
                    isBreak = false;
                }
                else if (i<str.size()-3 && str.substr(i+2,2).compare("RL") == 0)
                {
                    str.erase(i+2,2);
                    i--;
                    isBreak = false;
                }
            }
        }
        if (isBreak) break;
    }


    while(1)
    {
        bool isBreak = true;
        for (int i=0; i<str.size()-1; i++)
        {
            if (str.substr(i,2).compare("RL") == 0)
            {
                str.erase(i,1);
            }
        }
        if (isBreak) break;
    }



    cout<<str.size()<<endl;
    return 0;
}
