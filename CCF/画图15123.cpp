#include <iostream>
#include <memory.h>
using namespace std;

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

void DrawChar(char img[100][100], int n, int m, int x, int y, char ch)
{
	if (x < 0 || x >= m || y < 0 || y >= n) return;
	if (img[y][x] == '-' || img[y][x] == '|' || img[y][x] == '+') return;
	if (img[y][x] == ch) return;
	img[y][x] = ch;
	DrawChar(img,n,m,x+1,y,ch);
	DrawChar(img,n,m,x-1,y,ch);
	DrawChar(img,n,m,x,y+1,ch);
	DrawChar(img,n,m,x,y-1,ch);
}


int main()
{
	int n,m,q;
	cin>>m>>n>>q;
	
	char img[100][100];
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			img[i][j] = '.';
	
	for (int i=0; i<q; i++)
	{
		int op;
		cin>>op;
		if (op == 0)
		{
			int x1,x2,y1,y2;
			cin>>x1>>y1>>x2>>y2;
			if (x1 == x2)//ÊúÏß
			{
				for (int y=min(y1,y2); y<=max(y1,y2); y++)
				{
					if (img[y][x1] == '-' || img[y][x1] == '+')
						img[y][x1] = '+';
					else
						img[y][x1] = '|';
				}
			}
			else if (y1 == y2)//ºáÏß 
			{
				for (int x=min(x1,x2); x<=max(x1,x2); x++)
				{
					if (img[y1][x] == '|' || img[y1][x] == '+')
						img[y1][x] = '+';
					else
						img[y1][x] = '-';
				}
			}
		}
		else if (op == 1)
		{
			int x,y;
			char ch;
			cin>>x>>y>>ch;
			
			DrawChar(img,n,m,x,y,ch);
		}
	}
	
	
	for (int i=n-1; i>=0; i--)
	{
		for (int j=0; j<m; j++)
		{
			cout<<img[i][j];
		}
		cout<<endl;
	}
	return 0;
}
