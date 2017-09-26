


# include <limits>

using namespace std;

/**********************
*******************
************开始写代码**********/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int findLCS(string str1,string str2) {
    if(0 == str1.size() || 0 == str2.size())
        return 0;
    vector<vector<int> > array(str1.size()+1,vector<int>(str2.size()+1,0));
    for(size_t i=1; i<= str1.size(); ++i){
        for(size_t j=1; j<= str2.size(); ++j){
            if(str1[i-1] == str2[j-1]){
                array[i][j]=array[i-1][j-1]+1;
                }
            else
                array[i][j]=max(array[i-1][j],array[i][j-1]);
        }
    }
    return array[str1.size()][str2.size()];
}

bool fun(string str){
    string rstr=str;
    reverse(rstr.begin(),rstr.end());
    int diff=(int)str.size()-findLCS(str,rstr);
    return diff<2? true: false;
}

/*************结束写代码*********/

int main()
{
    bool res;
    string _str;
    getline(cin, _str);
    res=fun(_str);
    cout<<res<<endl;
    return 0;
}
