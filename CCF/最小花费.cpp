#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	int dest;
	int cost;
	Node();
	Node(int dest1,int cost1)
	{
		dest = dest1;
		cost = cost1;
	};
};

int main()
{	
	int n,m;
	cin>>n>>m;
	int *w = new int[n];
	for (int i=0; i<n; i++)
	{
		cin>>w[i];
	}
	vector< vector<Node> > table;
	table.resize(n);
	for (int i=0; i<n-1; i++)
	{
		int u,v,e;
		cin>>u>>v>>e;
		u--;
		v--;
		Node node1(v,e);
		table[u].push_back(node1);
		Node node2(u,e);
		table[v].push_back(node2);
	}
	int *source = new int[m];
	int *dest = new int[m];
	int *weight = new int[m];
	for (int i=0; i<m; i++)
	{
		cin>>source[i]>>dest[i];
		source[i]--;
		dest[i]--;
	}
	for (int i=0; i<m; i++)
	{
		int s = source[i];
		int d = dest[i];
		vector< vector<int> > paths;
		paths.resize(n);
		bool *visited = new bool[n];
		int *dis = new int[n];
		for (int j=0; j<n; j++)
		{
			visited[j] = false;
			dis[j] = INT_MAX;
		}
		visited[s] = true;
		dis[s] = 0;
		paths[s].push_back(s);
		for (size_t j=0; j<table[s].size(); j++)
		{
			dis[table[s][j].dest] = table[s][j].cost;
			for (size_t k=0; k<paths[s].size(); k++)
			{
				paths[table[s][j].dest].push_back(paths[s][k]);
			}
			paths[table[s][j].dest].push_back(table[s][j].dest);
		}
		while(1)
		{
			int minDis = INT_MAX;
			int minId = -1;
			for (int j=0; j<n; j++)
			{
				if (visited[j]) continue;
				if (minDis > dis[j])
				{
					minDis = dis[j];
					minId = j;
				}
			}
			if (minDis == INT_MAX) break;
			visited[minId] = true;
			for (size_t j=0; j<table[minId].size(); j++)
			{
				if (dis[minId]+table[minId][j].cost < dis[table[minId][j].dest])
				{
					dis[table[minId][j].dest] = table[minId][j].cost+dis[minId];
					paths[table[minId][j].dest].clear();
					for (size_t k=0; k<paths[minId].size(); k++)
					{
						paths[table[minId][j].dest].push_back(paths[minId][k]);
					}
					paths[table[minId][j].dest].push_back(table[minId][j].dest);
				}
			}
		}
		int minWeight = w[s];
		weight[i] = 0;
		for (size_t j=1; j<paths[d].size(); j++)
		{
			int len = -1;
			for (size_t k=0; k<table[paths[d][j-1]].size(); k++)
			{
				if (table[paths[d][j-1]][k].dest == paths[d][j])
				{
					len = table[paths[d][j-1]][k].cost;
					break;
				}
			}
			if (len == -1) break;
			weight[i] += minWeight * len;
			if (w[paths[d][j]] < minWeight)
			{
				minWeight = w[paths[d][j]];
			}
		}

	}

	for (int i=0; i<m; i++)
	{
		cout<<weight[i]<<endl;
	}
	return 0;
}
