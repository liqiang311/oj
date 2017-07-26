#include <iostream>
#include <map>
using namespace std;

int main()
{
	map<int,int> table;
	int n;
	cin>>n;
	int res = 0;
	for (int i=0; i<n; i++)
	{
		int tmp;
		cin>>tmp;
		if (table[tmp*-1] == 1) res++;
		table[tmp] = 1; 
	}
	cout<<res<<endl;
	
	return 0; 
}
