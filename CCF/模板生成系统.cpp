#include <iostream>
#include <memory.h>
#include <string.h>
using namespace std;

int main()
{
	//输入 
	int m,n;
	cin>>m>>n;
	getchar();
	int size = 10000;
	char **s = new char*[m];
	for (int i=0; i<m; i++)
	{
		s[i] = new char[size];
		cin.getline(s[i],size,'\n');
	}
	char **varName = new char*[n];
	char **varValue = new char*[n];
	for (int i=0; i<n; i++)
	{
		varName[i] = new char[256];//变量名 
		varValue[i] = new char[size];//变量值 
	}
	for (int i=0; i<n; i++)
	{
		cin.getline(varName[i],256,' ');
		cin.getline(varValue[i],size,'\n');//去掉双引号
		int j;
		for (j=0; j<strlen(varValue[i])-2; j++) 
		{
			varValue[i][j] = varValue[i][j+1];
		}
		varValue[i][j] = '\0';
	}
	//开始处理 
	for (int i=0; i<m; i++)
	{
		char *p = s[i];
		while(*p != '\0')
		{
			if (*p == '{' && *(p+1) == '{' && *(p+2) == ' ')
			{
				p += 3;
				//取变量名
				char tmpVarName[256];
				memset(tmpVarName,0,256);
				int j=0;
				while(*p != ' ')
				{
					tmpVarName[j++] = *p;
					p++;
				}
				tmpVarName[j] = '\0';
				//去变量库里寻找
				bool isFind = false;
				for (int k=0; k<n; k++)
				{
					if (strcmp(varName[k],tmpVarName) == 0)
					{
						isFind = true;
						//替换字符串p当前指向后面的空格
						if (strlen(varValue[k]) > strlen(tmpVarName)+6)//往后移
						{
							char *p1 = s[i] + strlen(s[i]);//指向结束符
							int step = strlen(varValue[k]) - strlen(tmpVarName) - 6;
							while(p1 != p+2)//p+2指向最后的一个右括弧
							{
								*(p1+step) = *p1;
								p1--;
							}
						}
						else if (strlen(varValue[k]) < strlen(tmpVarName)+6)//往前移 
						{
							char *p1 = p+3;//指向右括弧后一个 
							int step = strlen(tmpVarName)+6-strlen(varValue[k]);
							int len = strlen(s[i]);
							while(p1 != s[i] + len + 1)
							{
								*(p1-step) = *p1;
								p1++;
							}
						}
						//替换字符串从左括弧开始 
						memcpy(p-strlen(tmpVarName)-3,varValue[k],strlen(varValue[k]));
						p = p-strlen(tmpVarName)-3+strlen(varValue[k]);//指向新的起始位 
						break;
					}
				}
				//没找到,空
				if (isFind == false)
				{
					char *p1 = p+3;//指向有括弧 
					int step = strlen(tmpVarName)+6;
					int len = strlen(s[i]);
					while(p1 != s[i] + len + 1)
					{
						*(p1-step) = *p1;
						p1++;
					}
					p = p-strlen(tmpVarName)-3;//指向新的起始位 
				}
				p--;
			}
			p++;
		}
	}
	//显示 
	
	for (int i=0; i<m; i++)
		cout<<s[i]<<endl;
	return 0;
}
