#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	int *arr = new int[n];
	for (int i=0; i<n; i++) cin>>arr[i];
	
	map<int,int> table;
	for (int i=0; i<n; i++)
	{
		table[arr[i]] ++;
		cout<<table[arr[i]]<<" ";
	}
	cout<<endl;
	
	return 0;
}
