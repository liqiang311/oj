#include <iostream>
using namespace std;

bool f(int M, int S, int T, int *dis, int *time)
{
	if (S <= 0) return true;//到达出口
	if (T <= 0) return false;//时间耗尽
	if (M == 0 || M == 1)
	{
		*dis += 17;
		*time += 1;
		return f(M,S-17,T-1,dis,time);
	}
	else if (M == 2 || M == 3)
	{
		//若时间还有超过3s，可在3s内前进60m
		if (T >= 3)
		{
			*dis += 60;
			*time += 3;
			return f(M+8-10,S-60,T-3,dis,time);
		}
		else
		{
			*dis += 17;
			*time += 1;
			return f(M,S-17,T-1,dis,time);
		}
	}
	else if (M == 4 || M == 5)
	{
		//若时间还有超过2s，可在2s内前进60m
		*dis += 60;
		*time += 1;
		return f(M-10,S-60,T-1,dis,time);
	}
}


int main()
{
	int M,S,T;
	cin>>M>>S>>T;
	int dis=0,time=0;
	if (f(M,S,T,&dis,&time))
		cout<<"Yes "<<time<<endl;
	else
		cout<<"No "<<dis<<endl;
}