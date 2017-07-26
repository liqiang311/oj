#include <iostream>
#include <memory.h>
using namespace std;

struct lqRECT
{
	int x1,y1,x2,y2;
};

struct lqPOINT
{
	int x,y;
};

void FillRect(unsigned char screen[1439][2559], lqRECT area, int val)
{
	for (int y=area.y1; y<=area.y2; y++)
	{
		for (int x=area.x1; x<=area.x2; x++)
		{
			screen[y][x] = val;
		}
	}
}

int main()
{
	int N,M;
	cin>>N>>M;
	
	static unsigned char screen[1439][2559];
	memset(screen,0,1439*2559);
	lqRECT *rects = new lqRECT[N+1];
	for (int i=1; i<=N; i++)
	{
		cin>>rects[i].x1;
		cin>>rects[i].y1;
		cin>>rects[i].x2;
		cin>>rects[i].y2;
		FillRect(screen,rects[i],i);
	}
	lqPOINT *points = new lqPOINT[M];
	for (int i=0; i<M; i++)
	{
		cin>>points[i].x>>points[i].y;
	}
	
	for (int i=0; i<M; i++)
	{
		if (screen[points[i].y][points[i].x] == 0)
			cout<<"IGNORED"<<endl;
		else
		{
			cout<<(int)screen[points[i].y][points[i].x]<<endl;
			FillRect(screen,rects[screen[points[i].y][points[i].x]],screen[points[i].y][points[i].x]);
		}
	}
	
	return 0;
}
