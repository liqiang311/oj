#include <iostream>
#include <memory.h>
using namespace std;

void FillRect(unsigned char axis[100][100],int x1, int y1, int x2, int y2)
{
	for (int y=y1; y<y2; y++)
	{
		for (int x=x1; x<x2; x++)
		{
			axis[y][x] = 1;
		}
	}
}

int main()
{
	unsigned char axis[100][100];
	memset(axis,0,100*100);
	
	int n;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		FillRect(axis,x1,y1,x2,y2);
	}
	int num=0;
	for (int i=0; i<100; i++)
	{
		for (int j=0; j<100; j++)
		{
			if (axis[i][j] == 1)
			{
				num++;
			}
		}
	}
	cout<<num<<endl;
	
	return 0;
}
