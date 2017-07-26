#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;

struct RECORD
{
	bool isBuy;
	float price;
	int num;
	bool isValid;
};

int main()
{
	//¼ÇÂ¼¼Û¸ñ
	map<float,int> prices;
	vector<RECORD> records;
	char buf[256];
	int line;
	while(cin>>buf)
	{
		if (strcmp(buf,"buy")!=0 && strcmp(buf,"sell")!=0 && strcmp(buf,"cancel")!=0) break;
		if (strcmp(buf,"cancel")==0)
		{
			cin>>line;
			records[line-1].isValid = false;
			RECORD r;
			r.isValid = false;
			records.push_back(r);
		}
		else
		{
			RECORD r;
			cin>>r.price>>r.num;
			r.isValid = true;
			if (strcmp(buf,"buy")==0)
				r.isBuy = true;
			else
				r.isBuy = false;
			records.push_back(r);
			prices[r.price] = 1;
		}
	}
	int maxNum = 0;
	float propPrice = 0;
	map<float,int>::iterator it;
	for (it=prices.begin(); it!=prices.end(); it++)
	{
		float price = it->first;
		int buyNum=0;
		int sellNum=0;
		for (int i=0; i<records.size(); i++)
		{
			if (records[i].isValid == false) continue;
			if (records[i].isBuy && records[i].price >= price)
			{
				buyNum += records[i].num;
			}
			if (!records[i].isBuy && records[i].price <= price)
			{
				sellNum += records[i].num;
			}
		}
		if (min(sellNum,buyNum) >= maxNum)
		{
			maxNum = min(sellNum,buyNum);
			propPrice = max(propPrice,price);
		}
	}
	sprintf(buf,"%.2f %d",propPrice,maxNum);
	cout<<buf<<endl;
	return 0;
}
/*
buy 9.25 100
buy 8.88 175
sell 9.00 1000
buy 9.00 400
sell 8.92 400
cancel 1
buy 100.00 50
*/
