#include <iostream>
using namespace std;

bool f(int M, int S, int T, int *dis, int *time)
{
	if (S <= 0) return true;//�������
	if (T <= 0) return false;//ʱ��ľ�
	if (M == 0 || M == 1)
	{
		*dis += 17;
		*time += 1;
		return f(M,S-17,T-1,dis,time);
	}
	else if (M == 2 || M == 3)
	{
		//��ʱ�仹�г���3s������3s��ǰ��60m
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
		//��ʱ�仹�г���2s������2s��ǰ��60m
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