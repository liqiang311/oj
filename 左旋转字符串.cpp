// 001_����ת�ַ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "1234abcd";
	Left(s,2);
	cout<<s<<endl;

	getchar();
	return 0;
}
//���η�ת
void Reverse(char *Start,char *End)
{
	if (Start == NULL || End == NULL)
		return;
	while(Start < End)
	{
		char tmp = *Start;
		*Start = *End;
		*End = tmp;
		Start ++;
		End --;
	}
}
void Left(char *S,int Pos)
{
	int len = strlen(S);
	Pos %= len;
	Reverse(S,S+Pos-1);
	Reverse(S+Pos,S+len-1);
	Reverse(S,S+len-1);
}