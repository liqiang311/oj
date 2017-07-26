#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define INT_MAX	2147483647

struct DingDan
{
	int x,y,c;
	DingDan(int x,int y,int c)
	{
		this->x = x;
		this->y = y;
		this->c = c;
	}
};

struct Point
{
	int x,y;
	
	Point(int x,int y)
	{
		this->x = x;
		this->y = y;
	}
};

void BFS(int G[1000][1000], int n, vector<Point> &point)
{
	if (point.empty()) return;
	vector<Point> nextPoints;
	
	for (int i=0; i<point.size(); i++)
	{
		//每个点的上下左右
		int x = point[i].x;
		int y = point[i].y;
		int s = G[y][x];
		
		int X[4],Y[4];
		
		X[0] = max(0, x-1);
		Y[0] = y;
		X[1] = min(n-1, x+1);
		Y[1] = y;
		X[2] = x;
		Y[2] = min(n-1, y+1);
		X[3] = x;
		Y[3] = max(0, y-1);
		
		for (int j=0; j<4; j++)
		{
			if (G[Y[j]][X[j]] != INT_MAX)
			{
				if (s+1 < G[Y[j]][X[j]])
				{
					G[Y[j]][X[j]] = s+1;
					nextPoints.push_back(Point(X[j],Y[j]));
				}
			}
		}	
	}
	
	point.clear();
	BFS(G,n,nextPoints);
}

int main()
{
	vector<DingDan> dingdan;
	vector<Point> point;
	static int G[1000][1000];
	int n,m,k,d;
	int x,y,c;
	
	for (int i=0; i<1000; i++)
	{
		for (int j=0; j<1000; j++)
		{
			G[i][j] = INT_MAX-1;
		}
	}
	
	cin>>n>>m>>k>>d;
	
	for (int i=0; i<m; i++)
	{
		cin>>x>>y;
		x--;
		y--;
		G[y][x] = 0;//送货点 
		point.push_back(Point(x,y));
	}
	for (int i=0; i<k; i++)
	{
		cin>>x>>y>>c;
		x--;
		y--;
		dingdan.push_back(DingDan(x,y,c));
	}
	for (int i=0; i<d; i++)
	{
		cin>>x>>y;
		x--;
		y--;
		G[y][x] = INT_MAX;//不可达点 
	}
	
	BFS(G,n,point);
	
	long long sum=0;
	for (int i=0; i<dingdan.size(); i++)
	{
		sum += G[dingdan[i].y][dingdan[i].x] * dingdan[i].c;
	}
	cout<<sum<<endl;
	return 0;
}
