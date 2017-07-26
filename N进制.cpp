#include <iostream>
#include <string>
using namespace std;

int getValue(string str, int pos, int n)
{
	int v = 100;
	if (str[pos] >= '0' && str[pos] <= '9')
	{
		v = str[pos] - '0';
	}
	else if (str[pos] >= 'a' && str[pos] <= 'z')
	{
		v = str[pos] - 'a' + 10;
	}
	if (v >= n)
	{
		return -1;
	}
	return v;
}

int main()
{
	int n;
	string str1,str2;
	cin>>n;
	cin>>str1;
	cin>>str2;
	int len1 = str1.size();
	int len2 = str2.size();
	int len = max(len1,len2)+1;
	int *arr = new int[len];
	memset(arr,0,sizeof(int)*len);
	int jinwei = 0;
	for (int i=0; i<len; i++)
	{
		int pos = len-1-i;
		int pos1 = len1-1-i;
		int pos2 = len2-1-i;
		int v1,v2;
		if (pos1 >=0 && pos2 >= 0)
		{
			v1 = getValue(str1,pos1,n);
			v2 = getValue(str2,pos2,n);
		}
		else if (pos1 >= 0)
		{
			v1 = getValue(str1,pos1,n);
			v2 = 0;
		}
		else if (pos2 >= 0)
		{
			v1 = 0;
			v2 = getValue(str2,pos2,n);
		}
		else
		{
			v1 = 0;
			v2 = 0;
		}

		if (v1 == -1 || v2 == -1)
		{
			cout<<"-1"<<endl;
			return 0;
		}

		arr[pos] = v1 + v2 + jinwei;
		if (arr[pos] >= n)
		{
			jinwei = 1;
			arr[pos] = arr[pos] % n;
		}
		else
		{
			jinwei = 0;
		}
	}

	bool isFirst = true;
	for (int i=0; i<len; i++)
	{
		if (arr[i] == 0)
		{
			if (isFirst) continue;
			else cout<<arr[i];
		}
		else
		{
			cout<<arr[i];
			isFirst = false;
		}
	}
	cout<<endl;
	return 0;
}