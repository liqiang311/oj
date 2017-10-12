#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node(int data)
    {
        this->data=data;
    }
    Node(){}
};

//相交时返回相交节点，不相交时返回NULL
Node *IsCross(Node *list1, Node *list2)
{
    //用p2,p2分别指向2个表头，不断后移，最后达到表尾时，p1=p2，说明相交
    Node *p1,*p2;
    p1=list1;
    p2=list2;
    int len1=0,len2=0,len;
     
    while(p1->next!=NULL) { p1=p1->next;len1++;}
    while(p2->next!=NULL) {p2=p2->next;len2++;}

    if(p1==p2)
    {
        p1=list1;
        p2=list2;
        //移动2个链表长度的差值
        if(len1>=len2)
        {
            len=len1-len2;
            while(len--) p1=p1->next;
        }
        else
        {
            len=len2-len1;
            while(len--) p2=p2->next;
        }
        while(1)
        {
            if(p1==p2) return p1;
            else if(p1->next && p2->next)
            {
                p1=p1->next;
                p2=p2->next;
            }
        }
    }
    return NULL;  
}
