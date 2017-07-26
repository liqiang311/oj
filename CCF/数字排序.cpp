#include <iostream>
#include <map>
using namespace std;

int main()
{
	//ÊäÈë 
	int n;
	cin>>n;
	map<int,int> table;
	int tmp;
	for (int i=0; i<n; i++)
	{
		cin>>tmp;
		map<int,int>::iterator it;
		it = table.find(tmp);
		if (it == table.end())
			table[tmp] = 1;
		else
			table[tmp] ++;
	}
	/*
	for (map<int,int>::iterator it=table.begin(); it!=table.end(); it++)
	{
		cout<<it->first<<" "<<it->second<<endl;
	}
	*/
	//·ÖÎö
	while (!table.empty())
	{
		int maxValue = 0;
		int minNum;
		map<int,int>::iterator tmp;
		for (map<int,int>::iterator it=table.begin(); it!=table.end(); it++)
		{
			if (it->second > maxValue)
			{
				maxValue = it->second;
				minNum = it->first;
				tmp = it;
			}
			else if (it->second == maxValue)
			{
				if (it->first < minNum)
				{
					tmp = it;
					minNum = it->first;
				}
			}
		}
		table.erase(tmp);
		/*
		for (map<int,int>::iterator it=table.begin(); it!=table.end(); it++)
		{
			cout<<it->first<<" "<<it->second<<endl;
		}
		cout<<endl;*/
		cout<<minNum<<" "<<maxValue<<endl;
	}
	return 0;
}
