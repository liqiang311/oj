#include <iostream>
#include <memory.h>
#include <string.h>
using namespace std;

int main()
{
	//���� 
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
		varName[i] = new char[256];//������ 
		varValue[i] = new char[size];//����ֵ 
	}
	for (int i=0; i<n; i++)
	{
		cin.getline(varName[i],256,' ');
		cin.getline(varValue[i],size,'\n');//ȥ��˫����
		int j;
		for (j=0; j<strlen(varValue[i])-2; j++) 
		{
			varValue[i][j] = varValue[i][j+1];
		}
		varValue[i][j] = '\0';
	}
	//��ʼ���� 
	for (int i=0; i<m; i++)
	{
		char *p = s[i];
		while(*p != '\0')
		{
			if (*p == '{' && *(p+1) == '{' && *(p+2) == ' ')
			{
				p += 3;
				//ȡ������
				char tmpVarName[256];
				memset(tmpVarName,0,256);
				int j=0;
				while(*p != ' ')
				{
					tmpVarName[j++] = *p;
					p++;
				}
				tmpVarName[j] = '\0';
				//ȥ��������Ѱ��
				bool isFind = false;
				for (int k=0; k<n; k++)
				{
					if (strcmp(varName[k],tmpVarName) == 0)
					{
						isFind = true;
						//�滻�ַ���p��ǰָ�����Ŀո�
						if (strlen(varValue[k]) > strlen(tmpVarName)+6)//������
						{
							char *p1 = s[i] + strlen(s[i]);//ָ�������
							int step = strlen(varValue[k]) - strlen(tmpVarName) - 6;
							while(p1 != p+2)//p+2ָ������һ��������
							{
								*(p1+step) = *p1;
								p1--;
							}
						}
						else if (strlen(varValue[k]) < strlen(tmpVarName)+6)//��ǰ�� 
						{
							char *p1 = p+3;//ָ����������һ�� 
							int step = strlen(tmpVarName)+6-strlen(varValue[k]);
							int len = strlen(s[i]);
							while(p1 != s[i] + len + 1)
							{
								*(p1-step) = *p1;
								p1++;
							}
						}
						//�滻�ַ�������������ʼ 
						memcpy(p-strlen(tmpVarName)-3,varValue[k],strlen(varValue[k]));
						p = p-strlen(tmpVarName)-3+strlen(varValue[k]);//ָ���µ���ʼλ 
						break;
					}
				}
				//û�ҵ�,��
				if (isFind == false)
				{
					char *p1 = p+3;//ָ�������� 
					int step = strlen(tmpVarName)+6;
					int len = strlen(s[i]);
					while(p1 != s[i] + len + 1)
					{
						*(p1-step) = *p1;
						p1++;
					}
					p = p-strlen(tmpVarName)-3;//ָ���µ���ʼλ 
				}
				p--;
			}
			p++;
		}
	}
	//��ʾ 
	
	for (int i=0; i<m; i++)
		cout<<s[i]<<endl;
	return 0;
}
