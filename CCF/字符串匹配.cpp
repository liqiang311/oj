#include <iostream>
#include <memory.h>
#include <string.h>
using namespace std;

bool isMatch(char *s1, char *s2, bool isSense)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int len = len1 > len2 ? len2 : len1;
	for (int i=0; i<len; i++)
	{
		if (isSense)
		{
			if (s1[i] != s2[i]) return false;
		}
		else
		{
			char c1 = s1[i] > 'Z' ? s1[i]-('a'-'A') : s1[i];
			char c2 = s2[i] > 'Z' ? s2[i]-('a'-'A') : s2[i];
			if (c1 != c2) return false;
		}
		
	}
	return true;
}

int main()
{
	char S[100];
	char txt[100][100];
	int n;
	int len,Slen;
	bool isSense;
	int tmp;
	
	cin>>S;
	cin>>tmp;
	if (tmp) isSense = true;
	else isSense = false;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		cin>>txt[i];
	}
	
	Slen = strlen(S);
	for (int i=0; i<n; i++)
	{
		len = strlen(txt[i]);
		for (int j=0; j<len-Slen+1; j++)
		{
			if (isMatch(txt[i]+j,S,isSense))
			{
				cout<<txt[i]<<endl;
				break;
			}
		}
	}
	
	
	return 0;
}
