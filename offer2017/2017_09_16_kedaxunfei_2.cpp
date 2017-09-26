#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <map>
using namespace std;

bool isNum(string str)  
{  
    stringstream sin(str);  
    double d;  
    char c;  
    if(!(sin >> d))  
        return false;  
    if (sin >> c)  
        return false;  
    return true;  
}  

int main()
{
    string s;
    map<string, int> score;
    map<string, int> jinsheng;
    map<string, int> jinqiu;

    cin>>s;
    while(1)
    {
        if (isNum(s))
        {
            int n = atoi(s.c_str());
            for (int i=0; i<n; i++)
            {
                cin >> s;
                score[s] = 0;
                jinsheng[s] = 0;
                jinqiu[s] = 0;
            }
            while(1)
            {
                cin>>s;
                if (isNum(s)) break;
                int split1 = s.find('-');
                int split2 = s.find(' ');
                int split3 = s.find(':');
                string name1 = s.substr(0, split1);
                cout<<name1<<endl;
                string name2 = s.substr(split1+1, split2-split1-1);
                cout<<name2<<endl;
                int score1 = atoi(s.substr(split2+1, split3 - split2 - 1).c_str());
                int score2 = atoi(s.substr(split3+1, s.size()-split3).c_str());
                cout<<score1<< " "<<score2<<endl;
            }
        }
    }

    return 0;
}

/*
4
A
B
C
D
A-B 1:1
A-C 2:2
A-D 1:0
B-C 1:0
B-D 0:3
C-D 0:3
2
a
A
a-A 2:1
*/
