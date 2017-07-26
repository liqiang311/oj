#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

struct E
{
	int s,d;
	int w;

	E(int s,int d, int w)
	{
		this->s = s;
		this->d = d;
		this->w = w;	
	};
};

void Prim(int table[1000][1000], int n, int source, int res[1000][1000])
{
	vector<E> v;
	bool visited[1000];
	memset(visited,0,1000);
	visited[source] = true;
	for (int i=0; i<n; i++)
	{
		if (table[source][i] != -1)
		{
			v.push_back(E(source,i,table[source][i]));
		}
	}

	while(1)
	{
		//从v中找最小权重边
		int minIndex=-1, minWeight=2147483647;
		for (int i=0; i<v.size(); i++)
		{
			if (visited[v[i].s] && visited[v[i].d])
			{
				v.erase(v.begin()+i);
				i--;
			}
			else
			{
				if (v[i].w < minWeight)
				{
					minIndex = i;
					minWeight = v[i].w;
				}
			}
		}
		if (minIndex == -1) break;
		int s = v[minIndex].s;
		int d = v[minIndex].d;
		int w = v[minIndex].w;
		v.erase(v.begin()+minIndex);
		res[s][d] = w;
		visited[d] = true;
		for (int i=0; i<n; i++)
		{
			if (table[d][i] != -1)
			{
				if (!visited[i])
				{
					v.push_back(E(d,i,table[d][i]));
				}
			}
		}
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	static int table[1000][1000];
	static int res[1000][1000];
	for (int i=0; i<1000; i++)
	{
		for (int j=0; j<1000; j++)
		{
			table[i][j] = -1;
			res[i][j] = -1;
		}
	}

	for (int j=0; j<m; j++)
	{
		int x,y;
		cin>>x>>y;
		x--;
		y--;
		cin>>table[x][y];
		table[y][x] = table[x][y];
	}

	Prim(table,n,0,res);
	int num=0;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (res[i][j] != -1)
			{
				num += res[i][j];
			}
		}
	}
	cout<<num<<endl;
	
	return 0;
}
