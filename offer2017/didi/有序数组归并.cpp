#include <iostream>
#include <vector>
using namespace std;

//a,b数组必须有序
void Merge(vector<int> a, vector<int> b, vector<int> &c)
{
    c.resize(a.size()+b.size());

    int lenA = 0, lenB = 0, lenC = 0;

    while(lenA < a.size() && lenB < b.size())
    {
        if(a[lenA] < b[lenB])
        {
            c[lenC++] = a[lenA++];
        }
        else
        {
            c[lenC++] = b[lenB++];
        }
    }
    while(lenA < a.size())
    {
        c[lenC++] = a[lenA++];
    }

    while(lenB < b.size())
    {
        c[lenC++] = b[lenB++];
    }
}

int main() 
{
    int arrA[] = {1,2,3,3,4,5};
    vector<int> a(arrA, arrA + sizeof(arrA)/sizeof(int));
    int arrB[]={7,8,8,9};
    vector<int> b(arrB, arrB + sizeof(arrB)/sizeof(int));

    vector<int> c;
    Merge(a,b,c);
    for (int i=0; i<c.size(); i++) 
    {
        cout<<c[i]<<" ";
    }
    cout<<endl;
    return 0;
}
