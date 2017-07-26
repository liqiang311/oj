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
	//分析输入
	map<char,char> table;//0表示无参，1表示有参 
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
		//解析命令 
		for (int j=0; j<strlen(cmdArr[i]); j++)
		{
			if (cmdArr[i][j] == ' ')
			{
				//找下一个空格
				for (int k=j+1; k<strlen(cmdArr[i]); k++)
				{
					if (cmdArr[i][k] == ' ' || k == strlen(cmdArr[i])-1)
					{
						//j到k
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
	//分析,命令在cmd中存放
	//遍历每个cmd，在map中查找，找到无参，直接加入新map，找到有参，判断下一个是否有效，找到其他，则退出判断 
	map<char,string> *res = new map<char,string>[cmdNum];
	for (int i=0; i<cmdNum; i++)
	{
		for (int j=0; j<cmd[i].size(); j++)
		{
			//参数形式
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
				if (b == 1)//有参
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
				else//无参 
				{
					res[i][cmd[i][j][1]] = "";
				} 
			}
			else
				break;
		}
	}
	//输出
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
样例输出
Case 1: -a -l
Case 2:
Case 3: -w 15 -x
Case 4: -a -b
问题描述
　　请你写一个命令行分析程序,用以分析给定的命令行里包含哪些选项。
每个命令行由若干个字符串组成,它们之间恰好由一个空格分隔。
这些字符串中的第一个为该命令行工具的名字,由小写字母组成,你的程序不用对它进行处理。
在工具名字之后可能会包含若干选项,然后可能会包含一 些不是选项的参数。
　　选项有两类:带参数的选项和不带参数的选项。
一个合法的无参数选项的形式是一个减号后面跟单个小写字母,如"-a" 或"-b"。
而带参数选项则由两个由空格分隔的字符串构成,前者的格式要求与无参数选项相同,
后者则是该选项的参数,是由小写字母,数字和减号组成的非空字符串。
　　该命令行工具的作者提供给你一个格式字符串以指定他的命令行工具需要接受哪些选项。
这个字符串由若干小写字母和冒号组成,其中的每个小写字母表示一个该程序接受的选项。
如果该小写字母后面紧跟了一个冒号,它就表示一个带参数的选项,否则则为不带参数的选项。
例如, "ab:m:" 表示该程序接受三种选项,即"-a"(不带参数),"-b"(带参数), 以及"-m"(带参数)。
　　命令行工具的作者准备了若干条命令行用以测试你的程序。
对于每个命令行,你的工具应当一直向后分析。当你的工具遇到某个字符串既不是合法的选项,
又不是某个合法选项的参数时,分析就停止。命令行剩余的未分析部分不构成该命令的选项,因此你的程序应当忽略它们。
输入格式
　　输入的第一行是一个格式字符串,它至少包含一个字符,且长度不超过 52。
格式字符串只包含小写字母和冒号,保证每个小写字母至多出现一次,不会有两个相邻的冒号,也不会以冒号开头。
　　输入的第二行是一个正整数 N(1 ≤ N ≤ 20),表示你需要处理的命令行的个数。
　　接下来有 N 行,每行是一个待处理的命令行,它包括不超过 256 个字符。
该命令行一定是若干个由单个空格分隔的字符串构成,每个字符串里只包含小写字母,数字和减号。
输出格式
　　输出有 N 行。其中第 i 行以"Case i:" 开始,然后应当有恰好一个空格,
然后应当按照字母升序输出该命令行中用到的所有选项的名称,对于带参数的选项,在
输出它的名称之后还要输出它的参数。如果一个选项在命令行中出现了多次,只输出一次。
如果一个带参数的选项在命令行中出 现了多次,只输出最后一次出现时所带的参数。
样例输入
albw:x
4
ls -a -l -a documents -b
ls
ls -w 10 -x -w 15
ls -a -b -c -d -e -l
样例输出
Case 1: -a -l
Case 2:
Case 3: -w 15 -x
Case 4: -a -b
*/
