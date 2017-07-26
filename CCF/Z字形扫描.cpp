#include <iostream>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int **arr = new int*[n];
	for (int i=0; i<n; i++)
	{
		arr[i] = new int[n];
		for (int j=0; j<n; j++) cin>>arr[i][j];
	}
	for (int i=0; i<2*n-1; i++)
	{
		if (i % 2 == 1)
		{
			for (int j=0; j<=i; j++)
			{
				if (j >= 0 && j < n && i-j >=0 && i-j < n)
				{
					cout<<arr[j][i-j]<<" ";
				}
			}
		}
		else
		{
			for (int j=i; j>=0; j--)
			{
				if (j >= 0 && j < n && i-j >=0 && i-j < n)
				{
					cout<<arr[j][i-j]<<" ";
				}
			}
		}
	}
	return 0;
} 
