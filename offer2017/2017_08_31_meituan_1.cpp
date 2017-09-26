#include <iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int *p=new int[n];
    for (int i=0; i<n; i++) cin>>p[i];

    int num=1;
    for (int i=1; i<n; i++){
        if (p[i] != p[i-1]) num++;
    }
    cout<<num<<endl;

    delete[] p;
    return 0;
}
