#include <iostream>
#include <memory.h>
#include <string.h>
#include <map>
#include <math.h>
#include <vector>
using namespace std;

int main()
{
	//���� 
	int n,m,k,r;
	cin>>n>>m>>k>>r;
	int *exRx = new int[n];
	int *exRy = new int[n];
	int *unExRx = new int[m];
	int *unExRy = new int[m];
	for (int i=0; i<n; i++)
	{
		cin>>exRx[i]>>exRy[i];
	}
	for (int i=0; i<m; i++)
	{
		cin>>unExRx[i]>>unExRy[i];
	}
	//����
	//�����ڽӱ�,�洢ÿ���ڵ��ܵ���Ľ��
	vector<int> *table = new vector<int>[n+m];
	long long dis = r*(long long)r;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (j == i) continue;
			//������С�ڵ���r 
			if (abs(exRx[i]-exRx[j]) > r || abs(exRy[i]-exRy[j]) > r) continue;
			long long disx = exRx[i]-exRx[j];
			long long disy = exRy[i]-exRy[j];
			if (disx*disx + disy*disy > dis) continue;
			table[i].push_back(j);
		}
		for (int j=0; j<m; j++)
		{
			//������С�ڵ���r 
			if (abs(exRx[i]-unExRx[j]) > r || abs(exRy[i]-unExRy[j]) > r) continue;
			long long disx = exRx[i]-unExRx[j];
			long long disy = exRy[i]-unExRy[j];
			if (disx*disx + disy*disy > dis) continue;
			table[i].push_back(j+n);
		}
	}
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			//������С�ڵ���r 
			if (abs(unExRx[i]-exRx[j]) > r || abs(unExRy[i]-exRy[j]) > r) continue;
			long long disx = unExRx[i]-exRx[j];
			long long disy = unExRy[i]-exRy[j];
			if (disx*disx + disy*disy > dis) continue;
			table[i+n].push_back(j);
		}
		for (int j=0; j<m; j++)
		{
			if (j == i) continue;
			//������С�ڵ���r 
			if (abs(unExRx[i]-unExRx[j]) > r || abs(unExRy[i]-unExRy[j]) > r) continue;
			long long disx = unExRx[i]-unExRx[j];
			long long disy = unExRy[i]-unExRy[j];
			if (disx*disx + disy*disy > dis) continue;
			table[i+n].push_back(j+n);
		}
	}
	/*
	for (int i=0; i<n; i++)
	{
		cout<<exRx[i]<<","<<exRy[i]<<"::";
		for (int j=0; j<table[i].size(); j++)
		{
			if (table[i][j] < n)
				cout<<"    "<<exRx[table[i][j]]<<","<<exRy[table[i][j]]<<"(1)";
			else
				cout<<"    "<<unExRx[table[i][j]-n]<<","<<unExRy[table[i][j]-n]<<"(0)";
		}
		cout<<endl;
	}
	for (int i=0; i<m; i++)
	{
		cout<<unExRx[i]<<","<<unExRx[i]<<"::";
		for (int j=0; j<table[i].size(); j++)
		{
			if (table[i][j] < n)
				cout<<"    "<<exRx[table[i][j]]<<","<<exRy[table[i][j]]<<"(1)";
			else
				cout<<"    "<<unExRx[table[i][j]-n]<<","<<unExRy[table[i][j]-n]<<"(0)";
		}
		cout<<endl;
	}
	*/
	//����,����
	int *step=new int[n+m];//ÿ�������Ҫ��������
	for (int i=0; i<m+n; i++) step[i] = 1000;//���
	int *unusedK=new int[n+m];//����ÿ������ʣ���k����,��ʼȫ��Ϊk��
	for (int i=0; i<m+n; i++) unusedK[i] = k; 
	int queue[10000];//����
	int front=0,rear=0; 
	//��0��ʼ
	step[0] = 0;
	for (int i=0; i<table[0].size(); i++)
	{
		if (table[0][i] >= n)//�ٵ� 
		{
			if (unusedK[0] > 0)//������
				unusedK[table[0][i]] = unusedK[0]-1;
			else
				continue;
		}
		step[table[0][i]] = step[0]+1;
		queue[front++] =  table[0][i];
	}
	while (front>rear)
	{
		//����
		int p = queue[rear++];
		for (int i=0; i<table[p].size(); i++)
		{
			if (table[p][i] >= n)//�ٵ� 
			{
				if (unusedK[p] > 0)//������
					unusedK[table[p][i]] = unusedK[p]-1;
				else
					continue;
			}
			if (step[table[p][i]] > step[p]+1)
			{
				queue[front++] =  table[p][i];
				step[table[p][i]] = step[p]+1;
			}
		}
	}
	/*for (int i=0; i<n+m;i++)
		cout<<step[i]<<endl;*/
	cout<<step[1]-1<<endl;
	return 0;
	
}
/*
��������
����Ŀǰ��һ���ܴ��ƽ�淿������ n ������·����,ÿ������·�������̶���ĳ�����ϡ��κ���������·����ֻҪ���벻���� r ���ܻ��ཨ���������ӡ�
������������,���� m �����԰ڷ�����·������λ�á����������Щλ����ѡ������ k �������µ�·������
�������Ŀ����ʹ�õ� 1 ��·�����͵� 2 ��·����֮����������Ӿ��������ٵ���ת·���������������ŷ�������ת·���������ٸ����Ƕ���?
�����ʽ
������һ�а����ĸ������� n,m,k,r��(2 �� n �� 100,1 �� k �� m �� 100, 1 �� r �� 108)��
���������� n ��,ÿ�а����������� xi �� yi,��ʾһ���Ѿ����úõ����� ·������ (xi, yi) �㴦���������ݱ�֤�� 1 �͵� 2 ��·�����ڽ����� n ��·������������Ѿ����Ի�������(����һϵ�е���ת·����)��
���������� m ��,ÿ�а����������� xi �� yi,��ʾ (xi, yi) �㴦�������� һ��·������
�������������е�����ľ���ֵ������ 108,��֤�����е����������ͬ��
�����ʽ
�������ֻ��һ����,����ָ����λ�������� k ��·������,�ӵ� 1 ��· �������� 2 ��·�������پ�������ת·�����ĸ�����
��������
5 3 1 30000000
0 0
5 5
0 3
0 5
3 5
3 3
4 4
3 0
�������
2
*/
