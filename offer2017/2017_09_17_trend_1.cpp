#include <iostream>
#include <vector>

using namespace std;

struct People
{
    int id;
    int life;// 0 -dead 1,2 -live
    bool leftLive;
    bool rightLive;
};

int Joseph(int n, int m)
{
    int k = 0;
    vector<People> v;
    for (int i=0; i<n; i++)
    {
        People p;
        p.id = i;
        p.life = 1;
        p.leftLive = true;
        p.rightLive = true;
        v.push_back(p);
    }

    while(v.size() > 1){
        k = (k+m-1) % v.size();
        if (v[k].life == 1){//out
            int left = (k+v.size()-1)%v.size();
            if (!v[left].leftLive && v[left].rightLive)//life+1
                v[left].life++;
            v[left].rightLive = false;

            int right = (k+v.size()+1)%v.size();
            if (!v[right].rightLive && v[right].leftLive)//life+1
                v[right].life++;
            v[right].leftLive = false;

        }
        v[k].life --;

        //cout<<v[k].id+1<<endl;

        if (v[k].life == 0){
            v.erase(v.begin()+k);
        }

        //for (int i=0; i<v.size(); i++)
        //    cout<<v[i].id+1<<" ";
        //cout<<endl;
    }
    return v[0].id+1;
}

int main()
{
    cout<<"最后剩余的人为："<<Joseph(10, 3)<<endl;
}
