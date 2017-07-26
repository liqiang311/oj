#include <iostream>
#include <memory.h>
#include <string.h>
#include <map>
#include <math.h>
#include <vector>
using namespace std;

int main()
{
	//输入 
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
	//分析
	//建立邻接表,存储每个节点能到达的结点
	vector<int> *table = new vector<int>[n+m];
	long long dis = r*(long long)r;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (j == i) continue;
			//若距离小于等于r 
			if (abs(exRx[i]-exRx[j]) > r || abs(exRy[i]-exRy[j]) > r) continue;
			long long disx = exRx[i]-exRx[j];
			long long disy = exRy[i]-exRy[j];
			if (disx*disx + disy*disy > dis) continue;
			table[i].push_back(j);
		}
		for (int j=0; j<m; j++)
		{
			//若距离小于等于r 
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
			//若距离小于等于r 
			if (abs(unExRx[i]-exRx[j]) > r || abs(unExRy[i]-exRy[j]) > r) continue;
			long long disx = unExRx[i]-exRx[j];
			long long disy = unExRy[i]-exRy[j];
			if (disx*disx + disy*disy > dis) continue;
			table[i+n].push_back(j);
		}
		for (int j=0; j<m; j++)
		{
			if (j == i) continue;
			//若距离小于等于r 
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
	//处理,广搜
	int *step=new int[n+m];//每个结点需要几步到达
	for (int i=0; i<m+n; i++) step[i] = 1000;//最大
	int *unusedK=new int[n+m];//到达每个结点后剩余的k个数,初始全部为k个
	for (int i=0; i<m+n; i++) unusedK[i] = k; 
	int queue[10000];//队列
	int front=0,rear=0; 
	//从0开始
	step[0] = 0;
	for (int i=0; i<table[0].size(); i++)
	{
		if (table[0][i] >= n)//假的 
		{
			if (unusedK[0] > 0)//可以用
				unusedK[table[0][i]] = unusedK[0]-1;
			else
				continue;
		}
		step[table[0][i]] = step[0]+1;
		queue[front++] =  table[0][i];
	}
	while (front>rear)
	{
		//出队
		int p = queue[rear++];
		for (int i=0; i<table[p].size(); i++)
		{
			if (table[p][i] >= n)//假的 
			{
				if (unusedK[p] > 0)//可以用
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
问题描述
　　目前在一个很大的平面房间里有 n 个无线路由器,每个无线路由器都固定在某个点上。任何两个无线路由器只要距离不超过 r 就能互相建立网络连接。
　　除此以外,另有 m 个可以摆放无线路由器的位置。你可以在这些位置中选择至多 k 个增设新的路由器。
　　你的目标是使得第 1 个路由器和第 2 个路由器之间的网络连接经过尽量少的中转路由器。请问在最优方案下中转路由器的最少个数是多少?
输入格式
　　第一行包含四个正整数 n,m,k,r。(2 ≤ n ≤ 100,1 ≤ k ≤ m ≤ 100, 1 ≤ r ≤ 108)。
　　接下来 n 行,每行包含两个整数 xi 和 yi,表示一个已经放置好的无线 路由器在 (xi, yi) 点处。输入数据保证第 1 和第 2 个路由器在仅有这 n 个路由器的情况下已经可以互相连接(经过一系列的中转路由器)。
　　接下来 m 行,每行包含两个整数 xi 和 yi,表示 (xi, yi) 点处可以增设 一个路由器。
　　输入中所有的坐标的绝对值不超过 108,保证输入中的坐标各不相同。
输出格式
　　输出只有一个数,即在指定的位置中增设 k 个路由器后,从第 1 个路 由器到第 2 个路由器最少经过的中转路由器的个数。
样例输入
5 3 1 30000000
0 0
5 5
0 3
0 5
3 5
3 3
4 4
3 0
样例输出
2
*/
