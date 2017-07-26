#include <iostream>
using namespace std;

int main()
{
	//输入
	char buf[256];
	cin>>buf;
	//将输入放入数组中
	int arr[9];
	arr[0] = buf[0]-'0';
	for (int i=2; i<=4; i++)
		arr[i-1] = buf[i]-'0';
	for (int i=6; i<=10; i++)
		arr[i-2] = buf[i]-'0';
	//计算识别码
	int sum=0;
	for (int i=0; i<9; i++)
	{
		sum += arr[i] * (i+1);
	}
	sum %= 11;
	if (sum == 10)
	{
		//判断是否为X
		if (buf[12] == 'X')
		{
			cout<<"Right"<<endl;
		}
		else
		{
			buf[12] = 'X';
			buf[13] = '\0';
			cout<<buf<<endl;
		}
	}
	else
	{
		//判断是否为X
		if (buf[12] == sum+'0')
		{
			cout<<"Right"<<endl;
		}
		else
		{
			buf[12] = sum+'0';
			buf[13] = '\0';
			cout<<buf<<endl;
		}
	}
	return 0;
}