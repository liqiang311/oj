#include <iostream>
#include <string>
#include <vector>
using namespace std;


string annoncement(int numOfNeighbours, string characteristic){
    int N = numOfNeighbours;

    string res(N,'U');
    int rescnt = 0;

    for (int i=0; i<N; i++){

        if (characteristic[i] == 'n') continue;

        string tmp(N,'U');
        tmp[i] = 'I';

        for (int j=i; j>=0; j--){
            if (tmp[j] == 'I' && characteristic[j] == 'c'){
                if (j-1 >= 0) tmp[j-1] = 'I';
                if (j-2 >= 0) tmp[j-2] = 'I';
            }
        }
        for (int j=i; j<N; j++){
            if (tmp[j] == 'I' && characteristic[j] == 'c'){
                if (j+1 >= 0) tmp[j+1] = 'I';
                if (j+2 >= 0) tmp[j+2] = 'I';
            }
        }

        int cnt = 0;
        for (int j=0; j<N; j++)
            if (tmp[j] == 'I') cnt++;
        
        if (cnt > rescnt ){
            res = tmp;
            rescnt = cnt;
        }
        else if(cnt == rescnt && res.compare(tmp) > 0)
            res = tmp;

    }
    if (rescnt == 0) res[0] = 'I';
    return res;
}

int main(){
    cout<<annoncement(8,"nncncnnn")<<endl;
    cout<<annoncement(18,"ncncncnnncnccncnnn")<<endl;
}
