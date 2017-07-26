#include <iostream>
#include <memory.h>
#include <string.h>
#include <map>
#include <vector>
using namespace std;

int main()
{
	char buf[256];
	cin>>buf;
	//��������
	map<char,char> table;//0��ʾ�޲Σ�1��ʾ�в� 
	for (int i=0; i<strlen(buf); i++)
	{
		if (i == strlen(buf)-1 && buf[i] != ':')
		{
			table[buf[i]] = 0;
		}
		else
		{
			if (buf[i] != ':' && buf[i+1] != ':')
				table[buf[i]] = 0;
			else if (buf[i] != ':' && buf[i+1] == ':')
				table[buf[i]] = 1;
			else
				continue;
		}
	}
	/*
	map<char,char>::iterator it;
	for (it=table.begin(); it!=table.end(); it++)
	{
		cout<<it->first<<" "<<(int)it->second<<endl;
	}
	*/
	int cmdNum;
	cin>>cmdNum;
	getchar();
	char ** cmdArr = new char*[cmdNum];
	vector<string> *cmd = new vector<string>[cmdNum];
	for (int i=0; i<cmdNum; i++)
	{
		cmdArr[i] = new char[256];
		cin.getline(cmdArr[i],256,'\n');
		//�������� 
		for (int j=0; j<strlen(cmdArr[i]); j++)
		{
			if (cmdArr[i][j] == ' ')
			{
				//����һ���ո�
				for (int k=j+1; k<strlen(cmdArr[i]); k++)
				{
					if (cmdArr[i][k] == ' ' || k == strlen(cmdArr[i])-1)
					{
						//j��k
						string s;
						if (cmdArr[i][k] == ' ')
							s.append(cmdArr[i]+j+1,k-j-1);
						else
							s.append(cmdArr[i]+j+1,k-j);
						//cout<<s<<endl;
						cmd[i].push_back(s);
						j = k-1;
						break;
					}
				} 
			}
		}
	}
	/*
	cout<<cmdNum<<endl;
	for (int i=0; i<cmdNum; i++)
		cout<<cmdArr[i]<<endl;
	*/
	//����,������cmd�д��
	//����ÿ��cmd����map�в��ң��ҵ��޲Σ�ֱ�Ӽ�����map���ҵ��вΣ��ж���һ���Ƿ���Ч���ҵ����������˳��ж� 
	map<char,string> *res = new map<char,string>[cmdNum];
	for (int i=0; i<cmdNum; i++)
	{
		for (int j=0; j<cmd[i].size(); j++)
		{
			//������ʽ
			if (cmd[i][j].size() == 2 && cmd[i][j][0] == '-')
			{
				map<char,char>::iterator it = table.find(cmd[i][j][1]);
				char b=0;
				if (it == table.end())
				{
					break;
				}
				else
				{
					b = it->second;	
				}
				if (b == 1)//�в�
				{
					bool isValid = true;
					for (int k=0; k<cmd[i][j+1].size(); k++)
					{
						if (!((cmd[i][j+1][k] >= 'a' && cmd[i][j+1][k] <= 'z') ||
							  (cmd[i][j+1][k] >= '0' && cmd[i][j+1][k] <= '9') ||
							  (cmd[i][j+1][k] == '-')
							  ))
						{
							isValid = false;
							break;
						}
					}
					if (isValid)
					{
						string s;
						s.append(cmd[i][j+1]);
						res[i][cmd[i][j][1]] = s;
						j++;
					}
					else break;
				}
				else//�޲� 
				{
					res[i][cmd[i][j][1]] = "";
				} 
			}
			else
				break;
		}
	}
	//���
	for (int i=0; i<cmdNum; i++)
	{
		cout<<"Case "<<i+1<<":";
		for (map<char,string>::iterator it=res[i].begin(); it!=res[i].end(); it++)
		{
			cout<<" -"<<it->first<<" "<<it->second;
		}
		cout<<endl;
	} 
	return 0;
	
}

/*
albw:x
4
ls -a -l -a documents -b
ls
ls -w 10 -x -w 15
ls1 -a -b -c -d -e -l
�������
Case 1: -a -l
Case 2:
Case 3: -w 15 -x
Case 4: -a -b
��������
��������дһ�������з�������,���Է����������������������Щѡ�
ÿ�������������ɸ��ַ������,����֮��ǡ����һ���ո�ָ���
��Щ�ַ����еĵ�һ��Ϊ�������й��ߵ�����,��Сд��ĸ���,��ĳ����ö������д���
�ڹ�������֮����ܻ��������ѡ��,Ȼ����ܻ����һ Щ����ѡ��Ĳ�����
����ѡ��������:��������ѡ��Ͳ���������ѡ�
һ���Ϸ����޲���ѡ�����ʽ��һ�����ź��������Сд��ĸ,��"-a" ��"-b"��
��������ѡ�����������ɿո�ָ����ַ�������,ǰ�ߵĸ�ʽҪ�����޲���ѡ����ͬ,
�������Ǹ�ѡ��Ĳ���,����Сд��ĸ,���ֺͼ�����ɵķǿ��ַ�����
�����������й��ߵ������ṩ����һ����ʽ�ַ�����ָ�����������й�����Ҫ������Щѡ�
����ַ���������Сд��ĸ��ð�����,���е�ÿ��Сд��ĸ��ʾһ���ó�����ܵ�ѡ�
�����Сд��ĸ���������һ��ð��,���ͱ�ʾһ����������ѡ��,������Ϊ����������ѡ�
����, "ab:m:" ��ʾ�ó����������ѡ��,��"-a"(��������),"-b"(������), �Լ�"-m"(������)��
���������й��ߵ�����׼�������������������Բ�����ĳ���
����ÿ��������,��Ĺ���Ӧ��һֱ������������Ĺ�������ĳ���ַ����Ȳ��ǺϷ���ѡ��,
�ֲ���ĳ���Ϸ�ѡ��Ĳ���ʱ,������ֹͣ��������ʣ���δ�������ֲ����ɸ������ѡ��,�����ĳ���Ӧ���������ǡ�
�����ʽ
��������ĵ�һ����һ����ʽ�ַ���,�����ٰ���һ���ַ�,�ҳ��Ȳ����� 52��
��ʽ�ַ���ֻ����Сд��ĸ��ð��,��֤ÿ��Сд��ĸ�������һ��,�������������ڵ�ð��,Ҳ������ð�ſ�ͷ��
��������ĵڶ�����һ�������� N(1 �� N �� 20),��ʾ����Ҫ����������еĸ�����
������������ N ��,ÿ����һ���������������,������������ 256 ���ַ���
��������һ�������ɸ��ɵ����ո�ָ����ַ�������,ÿ���ַ�����ֻ����Сд��ĸ,���ֺͼ��š�
�����ʽ
��������� N �С����е� i ����"Case i:" ��ʼ,Ȼ��Ӧ����ǡ��һ���ո�,
Ȼ��Ӧ��������ĸ������������������õ�������ѡ�������,���ڴ�������ѡ��,��
�����������֮��Ҫ������Ĳ��������һ��ѡ�����������г����˶��,ֻ���һ�Ρ�
���һ����������ѡ�����������г� ���˶��,ֻ������һ�γ���ʱ�����Ĳ�����
��������
albw:x
4
ls -a -l -a documents -b
ls
ls -w 10 -x -w 15
ls -a -b -c -d -e -l
�������
Case 1: -a -l
Case 2:
Case 3: -w 15 -x
Case 4: -a -b
*/
