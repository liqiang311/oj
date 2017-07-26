#include <iostream>
#include <string>
using namespace std;

string s1 = "ABCDEFGHLMNOPQRS";
string s2 = "DCGSRQPOM";
int g_count = 0;//比较次数

//轮询方法
int CompareString1(string LongString,string ShortString)
{
	for (int i=0; i<ShortString.length(); i++)
	{
		bool isEqual = false;
		for (int j=0; j<LongString.length(); j++)
		{
			g_count++;
			if (LongString.at(j) == ShortString.at(i))
			{
				isEqual = true;
				break;
			}
		}
		if (!isEqual)
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	cout<<CompareString1(s1,s2)<<endl;
	cout<<g_count<<endl;
	return 0;
}