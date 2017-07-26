#include <iostream>
#include <memory.h>
using namespace std;

void deleteRect(int rect[30][30], int i, int j, int n, int m, int res[30][30])
{
	bool isHor=false,isVer=false;
	
	if (i+2 < n) isVer = true;
	if (j+2 < m) isHor = true;
	
	int val = rect[i][j];
	
	int tmp;
	if (isHor)
	{
		tmp = j+1;
		while(tmp<m && rect[i][tmp] == val)
		{
			tmp++;
		}
		if (tmp-j >= 3)
		{
			tmp = j;
			while(tmp<m && rect[i][tmp] == val)
			{
				res[i][tmp] = 0;
				tmp++;
			}
		}
	}
	if (isVer)
	{
		tmp = i+1;
		while(tmp<n && rect[tmp][j] == val)
		{
			tmp++;
		}
		if (tmp-i >= 3)
		{
			tmp = i;
			rect[tmp][j] = val;
			while(tmp<n && rect[tmp][j] == val)
			{
				res[tmp][j] = 0;
				tmp++;
			}
		}
	}

}

int main()
{
	int n,m;
	cin>>n>>m;
	
	int rect[30][30];
	int res[30][30];
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			cin>>rect[i][j];
			res[i][j] = rect[i][j];
		}
	}
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			deleteRect(rect,i,j,n,m,res);
		}
	}
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			cout<<res[i][j]<<" ";
		}
		cout<<endl;
	}
	
	return 0;
}
