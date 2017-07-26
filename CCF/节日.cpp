#include <iostream>
#include <map>
using namespace std;

int MONTH[2][13] ={ {0,31,28,31,30,31,30,31,31,30,31,30,31},
					{0,31,29,31,30,31,30,31,31,30,31,30,31}};

bool isRunNian(int year)
{
	if (year % 400 == 0) return true;
	if (year % 4 == 0 && year % 100 != 0) return true;
	return false;
}
//某年的某月1号是星期几 
int week(int year,int month)
{
	int days = 0;
	for (int i=1850; i<year; i++)
	{
		if (isRunNian(i))
			days += 366;
		else
			days += 365;
	}
	if (isRunNian(year))
	{
		for (int i=1; i<month; i++)
		{
			days += MONTH[1][i];	
		}
	}
	else
	{
		for (int i=1; i<month; i++)
		{
			days += MONTH[0][i];	
		}
	}
	
	days = days % 7;
	return (2+days-1)%7+1;
}

int main()
{
	int a,b,c,y1,y2;
	cin>>a>>b>>c>>y1>>y2;
	
	//cout<<week(2016,4)<<endl;
	for (int y=y1; y<=y2; y++)
	{
		int d1 = week(y,a);
		int d2;
		if (c >= d1)
		{
			d2 = (b-1) * 7 + c - d1 + 1;
		}
		else
		{
			d2 = b * 7 - (d1 - c) + 1;
		}
		if (a == 2)
		{
			int tmp1;
			if (isRunNian(y))
				tmp1 = 29;
			else
				tmp1 = 28;
			if (d2 <= tmp1)
			{
				char buf[256];
				sprintf(buf,"%d/%02d/%02d",y,a,d2);
				cout<<buf<<endl;
			}
			else
			{
				cout<<"none"<<endl;
			}
		}
		else
		{
			if (d2 <= MONTH[0][a])
			{
				char buf[256];
				sprintf(buf,"%d/%02d/%02d",y,a,d2);
				cout<<buf<<endl;
			}
			else
			{
				cout<<"none"<<endl;
			}
		}
	}
	return 0;
}
