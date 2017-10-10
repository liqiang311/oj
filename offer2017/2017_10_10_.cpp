#include <iostream>
using namespace std;

int main()
{
    int num[3];
    char d;
    cin>>num[0]>>d>>num[1]>>d>>num[2];
    int res = num[0]^num[1]^num[2];
    if (res == 0) {
        cout<<"1"<<endl;
        return 0;
    }
    else {
        for (int i=1; i<=num[0]; i++)
        {
            int tmp = (num[0]-i)^num[1]^num[2];
            if (tmp == 0) {
                cout<<"a"<<","<<i<<endl;
                return 0;
            }
        }

        for (int i=1; i<=num[1]; i++)
        {
            int tmp = (num[1]-i)^num[0]^num[2];
            if (tmp == 0) {
                cout<<"b"<<","<<i<<endl;
                return 0;
            }
        }

        for (int i=1; i<=num[2]; i++)
        {
            int tmp = (num[2]-i)^num[0]^num[1];
            if (tmp == 0) {
                cout<<"c"<<","<<i<<endl;
                return 0;
            }
        }
    }
    return 0;
}
