#include <iostream>
using namespace std;

int GetEdgeLen(int **arr, int n, int m, int i, int j, int sign)
{
	int sum=0;
	for (int k=0; k<sign; k++)
	{
		for (int h=0; h<sign; h++)
		{
			sum += arr[i+k][j+h];
		}
	}
	if (sign*sign != sum) return -1;
	while(1)
	{
		sign ++;
		if (i+sign-1 >= n || j+sign-1 >= m) break;
		for (int k=0; k<sign; k++)
		{
			sum += arr[i+k][j+sign-1];
			sum += arr[i+sign-1][j+k];
		}
		sum -= arr[i+sign-1][j+sign-1];
		if (sum != sign * sign) break;
	}
	return sign-1;
}

int main()
{
	int N,M;
	cin>>N>>M;
	int **arr = new int *[N];
	for (int i=0; i<N; i++)
	{
		arr[i] = new int[M];
		for (int j=0; j<M; j++)
		{
			cin>>arr[i][j];
		}
	}
	int **sign = new int *[N];
	for (int i=0; i<N; i++)
		sign[i] = new int[M];

	for (int i=0; i<N; i++)
	{
		for (int j=0; j<M; j++)
		{
			sign[i][j] = 0;
			int i1,j1,i2,j2,i3,j3;
			i1 = max(i-1,0);
			j1 = max(j-1,0);
			i2 = max(i-1,0);
			j2 = j;
			i3 = i;
			j3 = max(j-1,0);
			sign[i][j] = max(sign[i][j],sign[i1][j1]-1);
			sign[i][j] = max(sign[i][j],sign[i2][j2]-1);
			sign[i][j] = max(sign[i][j],sign[i3][j3]-1);
			sign[i][j] = GetEdgeLen(arr,N,M,i,j,sign[i][j]);
		}
	}

	cout<<endl;
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<M; j++)
		{
			cout<<sign[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}