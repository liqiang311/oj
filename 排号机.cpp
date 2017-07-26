#include <iostream>
#include <vector>
using namespace std;


int main()
{
	char buf[256];
	char buf1[256];
	char buf2[256];

	vector<int> nor;
	vector<int> vip;
	vector<int> total;
	while(1)
	{
		cin.getline(buf,256);
		if (sscanf(buf,"%s %s",buf1,buf2) == 0)
		{
			cout<<"error"<<endl;
			continue;
		}
		if (strcmp(buf,"get") == 0)
		{
			if (total.empty())
				nor.push_back(1);
			else
				nor.push_back(total[total.size()-1]+1);
			total.push_back(nor[nor.size()-1]);
			cout<<nor[nor.size()-1]<<endl;
		}
		else if (strcmp(buf,"get vip") == 0)
		{
			if (total.empty())
				vip.push_back(1);
			else
				vip.push_back(total[total.size()-1]+1);
			total.push_back(vip[vip.size()-1]);
			cout<<"vip "<<vip[vip.size()-1]<<endl;
		}
		else if (strcmp(buf,"call") == 0)
		{
			if (vip.empty())
			{
				if (nor.empty())
				{
					cout<<"error"<<endl;
				}
				else
				{
					int p = nor[0];
					nor.erase(nor.begin());
					total.erase(total.begin());
					cout<<p<<endl;
				}
			}
			else
			{
				int p = vip[0];
				vip.erase(vip.begin());
				for (vector<int>::iterator it = total.begin(); it!=total.end(); it++)
				{
					if (*it == p)
					{
						total.erase(it);
						break;
					}
				}
				cout<<"vip "<<p<<endl;
			}
		}
		else if (strcmp(buf1,"delete") == 0)
		{
			int p;
			if (sscanf(buf2,"%d",&p) == 0)
			{
				cout<<"error"<<endl;
				continue;
			}
			vector<int>::iterator it = total.begin();
			for (; it!=total.end(); it++)
			{
				if (*it == p)
				{
					total.erase(it);
					break;
				}
			}
			if (it == total.end())
			{
				cout<<"error"<<endl;
			}
			else
			{
				for (it=vip.begin(); it!=vip.end(); it++)
				{
					if (*it == p)
					{
						vip.erase(it);
						cout<<"vip "<<p<<endl;
						break;
					}
				}
				if (it == vip.end())
				{
					for (it=nor.begin(); it!=nor.end(); it++)
					{
						if (*it == p)
						{
							nor.erase(it);
							cout<<p<<endl;
							break;
						}
					}
				}
			}
		}
		else if (strcmp(buf,"count") == 0)
		{
			cout<<total.size()<<endl;
		}
		else if (strcmp(buf1,"countN") == 0)
		{
			int p;
			if (sscanf(buf2,"%d",&p) == 0)
			{
				cout<<"error"<<endl;
				continue;
			}
			int num=0;
			vector<int>::iterator it;
			for (it=vip.begin(); it!=vip.end(); it++)
			{
				if (*it == p)
				{
					cout<<num<<endl;
					break;
				}
				num++;
			}
			if (it == vip.end())
			{
				for (it=nor.begin(); it!=nor.end(); it++)
				{
					if (*it == p)
					{
						cout<<num<<endl;
						break;
					}
					num++;
				}
			}
		}
		else if (strcmp(buf,"reset") == 0)
		{
			total.clear();
			nor.clear();
			vip.clear();
		}
		else if (strcmp(buf,"quit") == 0)
		{
			break;
		}
		else
		{
			cout<<"error"<<endl;
		}
	}
	return 0;
}


/*
IP��ַת��
����:	
IP��ַ�ĳ���Ϊ32������2^32-1����ַ��IP��ַһ����õ��ʮ���Ʊ�ʾ��������"192.168.1.1"��IP��ַҲ����ֱ����һ��32λ���������б�ʾ������ĿҪ����ݸ���������IP��ַ��ʾ��������ת��Ϊ���ʮ���Ƶ���ʽ��
�ٸ����ӣ�
��������IP��ַΪ 3232235777
���Ӧʮ������Ϊ 0xC0A80101
ÿ�ֽ�תΪʮ���� 0xC0=192��0xA8=168,0x01=1��0x01=1
�����Ϊ 192.168.1.1
����ʱ������:	1 Sec
�ڴ�����:	100 MByte
����:	
32λ������IP��ַ
���:	
���ʮ����IP��ַ
��������:	
3232235777
�������:	
192.168.1.1
����ʾ:	
��

*/