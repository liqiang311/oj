#include <iostream>
#include <map>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int *arr = new int[n];
	map<int,int> table;
	for (int i=0; i<n; i++)
	{
		cin>>arr[i];
		table[arr[i]] = 1;
	}
	
	int num=0;
	for (int i=0; i<n; i++)
	{
		if (table[arr[i]-1]==1) num++;
		if (table[arr[i]+1]==1) num++;
	}
	cout<<num/2<<endl;
	
	return 0;
}
