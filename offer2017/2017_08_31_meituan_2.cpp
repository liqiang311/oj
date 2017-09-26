#include <iostream>
#include <vector>
using namespace std;

bool IsOK(int *p, int n, bool *visited, int cur, vector<int> &page){
    bool isEnd = true;
    for (int i=0; i<n; i++)
        if (visited[i] == false) isEnd = false;
    if (isEnd){
        return true;
    }

    for (int i=0; i<n; i++){
        //决定下一组分给谁
        if (i != cur && visited[i] == false && page.size() >= p[i]){
            bool chongfu = false;
            for (int j=0; j<p[i]; j++){
                if (page[page.size()-1-j] == i){
                    chongfu = true;
                    break;
                }
            }
            if (chongfu) continue;

            vector<int> pageBack;
            for (int j=0; j<page.size(); j++)
                pageBack.push_back(page[j]);

            visited[i] = true;
            for (int j=0; j<p[i]; j++){
                page[page.size()-1-j] = i;
            }

            if (IsOK(p,n,visited,i,page)) return true;

            visited[i] = false;
            for (int j=0; j<page.size(); j++)
                page[j] = pageBack[j];
        }
    }
}

int main()
{
    int n;
    cin>>n;
    if (n < 2 || n> 30){
        cout<<"No"<<endl;
        return 0;
    }

    int *p=new int[n];
    for (int i=0; i<n; i++) cin>>p[i];

    bool *visited = new bool[n];
    for (int i=0; i<n; i++) visited = false;

    
    for (int i=0; i<n; i++)
    {
        //visited[i] = true;
        vector<int> page;
        for (int j=0; j<p[i]; j++)
            page.push_back(j);

        if (IsOK(p,n,visited,i,page)) {
            cout<<"Yes"<<endl;
            return 0;
        }
        //visited[i] = false;
    }
    cout<<"No"<<endl;
    return 0;
}
