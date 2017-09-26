#include <iostream>

#include <vector>

#include <numeric>

# include <limits>


using namespace std;

/**********************

*******************

************开始写代码**********/
long C(int n, int i) //C(n,m)
{
    int c = 1;
    for (int j=0; j<i; j++)
    {
        c *= (n-j);
    }
    for (int j=0; j<i; j++)
    {
        c /= (j+1);
    }   

    return c;
}

long fun(long x){
    if (x == 1) return 1;

    int n = 0;
    while(++n)
    {
        if (x > C(n,n/2)) continue;

        for (int i=1; i<n/2+1; i++)
        {
            if (C(n,i) == x) return n+1;
        }
    }
    return 0;
}

/*************结束写代码*********/

int main()
{
    cout<< fun(1) <<endl;
    cout<< fun(4) <<endl;
    cout<< fun(10) <<endl;
    return 0;
}
