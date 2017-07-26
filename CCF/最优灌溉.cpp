#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

#define NONE	-1

struct E
{
	int d;
	int w;
	
	E(int D,int W)
	{
		w = W;
		d = D;
	};
};

vector<vector<E> > g;

int Prim()
{
	int N = g.size(); 
	
	char v[1000];
	memset(v,0,1000);
	
	int dis[1000];
	for (int i=0; i<N; i++)
	{
		dis[i] = 99999999;
	}
	dis[0] = 0;
	int ans = 0;
	for (int i=0; i<N; i++)
	{
		int mark = -1;
		for (int j=0; j<N; j++)
		{
			if (v[j] == 0)
			{
				if (mark == -1)
				{
					mark = j;
				}
				else if (dis[j] < dis[mark])
				{
					mark = j;
				}
			}
		}
		if (mark == -1) break;
		v[mark] = 1;
		ans += dis[mark];
		for(int j=0; j<g[mark].size(); j++)
		{
			if (v[g[mark][j].d] == 0)
			{
				int x = g[mark][j].d;
				dis[x] = min(dis[x],g[mark][j].w);
			}
		}
	}
	return ans;
}

int main()
{
	int n,m;
	cin>>n>>m;
	g.resize(n);

	for (int i=0; i<m; i++)
	{
		int s,d,w;
		cin>>s>>d>>w;
		s--;
		d--;
		g[s].push_back(E(d,w));
		g[d].push_back(E(s,w));
	}
	
	cout<<Prim()<<endl;
	return 0;
}





/*



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

int Prim(int table[1000][1000], int n, int source)
{
	int res = 0;
	vector<E> v;
	bool visited[1000];
	memset(visited,0,1000);
	visited[source] = true;
	for (int i=0; i<n; i++)
	{
		if (table[source][i] != NONE)
		{
			v.push_back(E(source,i,table[source][i]));
		}
	}
	
	while(1)
	{
		//从v中找最小权重边
		int minIndex=-1, minWeight=9999999;
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
		res += w;
		visited[d] = true;
		for (int i=0; i<n; i++)
		{
			if (table[d][i] != NONE)
			{
				if (!visited[i])
				{
					v.push_back(E(d,i,table[d][i]));
				}
			}
		}
	}
	return res;
}

int main()
{
	int n,m;
	cin>>n>>m;
	static int table[1000][1000];
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			table[i][j] = NONE;
		}
	}

	for (int i=0; i<m; i++)
	{
		int s,d,w;
		cin>>s>>d>>w;
		s--;
		d--;
		if (table[s][d] == NONE)
			table[s][d] = table[d][s] = w;
		else
		{
			if (w < table[s][d])
			{
				table[s][d] = table[d][s] = w;
			}
		}
	}
	
	cout<<Prim(table,n,0)<<endl;
}


*/
