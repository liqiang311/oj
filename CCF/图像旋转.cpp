#include <iostream>
using namespace std;

int main()
{
	int n,m;
	cin>>n>>m;
	int **img = new int*[n];
	for (int i=0; i<n; i++)
	{
		img[i] = new int[m];
		for (int j=0; j<m; j++)
			cin>>img[i][j];
	}
	int **res = new int*[m];
	for (int i=0; i<m; i++)
	{
		res[i] = new int[n];
	}
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			res[i][j] = img[j][m-i-1];
		}
	}
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout<<res[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
