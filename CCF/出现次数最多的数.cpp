/*
��������
����n�����������ҳ������г��ִ�����������������������ж���������������С��һ����
�����ʽ
����ĵ�һ��ֻ��һ��������n(1 �� n �� 1000)����ʾ���ֵĸ�����

����ĵڶ�����n������s1, s2, ��, sn (1 �� si �� 10000, 1 �� i �� n)�����ڵ����ÿո�ָ���

�����ʽ
�����n�������г��ִ�����������������������ж�������������С��һ����
��������
6

10 1 10 20 30 20

�������
10

*/
#include <iostream>
#include <map>
using namespace std;

int main()
{
	int n;
	int m;
	cin>>n;
	map<int,int> table;

	for (int i=0; i<n; i++)
	{
		cin>>m;
		table[m] ++;
	}
	int maxNum;
	int maxCount = 0;
	map<int,int>::iterator it;
	for (it=table.begin(); it!=table.end(); it++)
	{
		if (it->second > maxCount)
		{
			maxNum = it->first;
			maxCount = it->second;
		}
	}
	cout<<maxNum<<endl;
	return 0;
}