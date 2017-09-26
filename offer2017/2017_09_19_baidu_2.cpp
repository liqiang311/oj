#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


int BitCount(unsigned int n)
{
    unsigned int c =0 ;
    for (c =0; n; n >>=1)
        c += n &1 ;
    return c ;
}

struct Node
{
    int bc;
    int id;
    int num;
};

int comp(const void *a, const void *b)
{
    Node *n1 = (struct Node *)a;
    Node *n2 = (struct Node *)b;
    if (n1->bc < n2->bc) return 1;
    else if(n1->bc > n2->bc) return -1;
    else return n1->num < n2->num ? 1 : -1;
}

vector<int> fun(int num, int element, int *streamNum)
{
    vector<Node> node;
    node.resize(num);

    for (int i=0; i<node.size(); i++)
    {
        node[i].bc = BitCount(streamNum[i]);
        node[i].id = i;
        node[i].num = streamNum[i];
    }

    qsort(node.data(), node.size(),sizeof(node[0]), comp);

    vector<int> res;
    for (int i=0; i<element; i++)
    {
        res.push_back(node[i].num);
    }
    return res;
}

int main(){
    int a[] = {5,3,7,1,2};
    vector<int> v = fun(5,2,a);
    for (int i=0; i<v.size(); i++)
        cout<<v[i]<<" ";
    cout<<endl;

    int a1[] = {19,32,15,24};
    vector<int> v1 = fun(4,3,a1);
    for (int i=0; i<v1.size(); i++)
        cout<<v1[i]<<" ";
    cout<<endl;
}
