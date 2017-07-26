#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

const int maxn = 10000;
const int maxm = 100000;

int father[maxn];
vector< pair<int,int> > adj[maxn];
bool vis[maxm];

int getFather(int x)
{
	return x == father[x] ? x : father[x] = getFather(father[x]);
}

void add(int x, int y, int z)
{
	adj[x].push_back(make_pair(z,y));
	adj[y].push_back(make_pair(z,x));
}

vector<int> path;

void dfs(int u)
{
	for (int it=0; it<adj[u].size(); it++)
	{
		if ( ! vis[adj[u][it].first])
		{
			vis[adj[u][it].first] = true;
			dfs(adj[u][it].second);
			path.push_back(adj[u][it].second);
		}
	}
}

bool solve()
{
	//所有节点的父亲节点是自己 
	for (int i=0; i<maxn; i++)
	{
		father[i] = i;
	}
	for (int i=0; i<maxn; i++)
	{
		for (int j=0; j<adj[i].size(); j++)
		{
			father[getFather(i)] = getFather(adj[i][j].second);
		}
	}
	int origin = -1;
	for (int i=0; i<maxn; i++)
	{
		if (!adj[i].empty())
		{
			if (adj[i].size() % 2 == 1)//奇数出度 
			{
				return false;
			}
			if (origin == -1)
			{
				origin = i;
			}
			if (getFather(i) != getFather(origin))
			{
				return false;
			}
			sort(adj[i].begin(),adj[i].end());
		}
	}
	path.clear();
	memset(vis,false,sizeof(vis));
	if (origin != -1)
	{
		dfs(origin);
	}
	reverse(path.begin(), path.end());
	
	return true;
}


int main()
{
	int n,m;
	cin>>n>>m;

	for (int i=0; i<m; i++)
	{
		int a,b;
		cin>>a>>b;
		a--;
		b--;
		adj[a].push_back(make_pair(i,b));
		//adj[b].push_back(make_pair(i,a));
	}

	solve();
	
	if (path.size())
	{
		for (int i=0; i<path.size(); i++)
		{
			cout<<path[i]+1<<" ";
		}
		cout<<endl;
	}
	else
	{
		cout<<"-1"<<endl;
	}
	return 0;
}

/*
bool isEuler(char G[10000][10000], int n, int e)
{
	int *count = new int[n];
	memset(count,0,sizeof(count));
	for (int i=0; i<n; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			if (G[i][j] == 1)
			{
				count[i] ++;
				count[j] ++;
			}
		}
	}
	int jishuNum = 0;
	bool ret = true;
	for (int i=0; i<n; i++)
	{
		if (count[i] == 0)
		{
			ret = false;
			break;
		}
		if (count[i] % 2 == 1)
			jishuNum++;
	}
	if (jishuNum > 2) ret = false;

	delete count;
	return ret;
}

void EulerDFS(char G[10000][10000], int n, int e, vector<int> &path, int curNode, int next)
{
	//找当前能走的边
	bool flag = true;//标记有无路可走 
	for (int i=next; i<n; i++)
	{
		if (G[curNode][i] == 1)
		{
			flag = false;
			G[curNode][i] = G[i][curNode] = 0;
			path.push_back(i);
			EulerDFS(G,n,e,path,i,0);
			break;//不继续执行，因为若不成功，就表明没路 
		}
	}
	if (flag)
	{
		//无路可走 
		if (path.size()-1 == e)
		{
			return;
		}
		else if (path.size() < 2)
		{
			return;
		}
		else
		{
			int q = path.back();
			path.pop_back();
			int p = path.back();
			G[p][q] = G[q][p] = 1;
			EulerDFS(G,n,e,path,p,q+1);
		}
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	static char G[10000][10000];
	memset(G,0,10000*10000);
	for (int i=0; i<m; i++)
	{
		int a,b;
		cin>>a>>b;
		a--;
		b--;
		G[a][b] = G[b][a] = 1;
	}

	vector<int> path;
	path.push_back(0);
	//if (isEuler(G,n,m))
		EulerDFS(G,n,m,path,0,0);

	if (path.size() == m+1)
	{
		for (int i=0; i<path.size(); i++)
		{
			cout<<path[i]+1<<" ";
		}
		cout<<endl;
	}
	else
	{
		cout<<"-1"<<endl;
	}
	return 0;
}
*/
