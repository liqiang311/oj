#include <iostream>
using namespace std;

struct Info
{
	int right,down;
};
/////////////////////////////////////////////////////
//
//  tableΪ������󣬴�ų�ʼ�Թ���Ϣ
//  nΪ����
//  mΪ����
//  ����ֵΪ��С�任����
//
/////////////////////////////////////////////////////
int DemoDay(char table[100][100], int n, int m)
{
	//step.1------------����ṹ��--------------------//
	Info info[100][100];
	//step.2------------��ʼ�����--------------------//
	info[0][0].right = 0;
	//������Ҳ��Ϊ�ϰ������Զ����������ƶ�
	if (table[0][1] == 'b') info[0][0].down = 0;
	else 					info[0][0].down = 1;
	//step.3------------��ʼ����һ��------------------//
	for (int i=1; i<m; i++)
	{
		//rightֵ�������rightֵ�������Ƿ�Ϊ�ϰ���Ӱ��
		if (table[0][i] == 'b') info[0][i].right = info[0][i-1].right + 1;
		else 					info[0][i].right = info[0][i-1].right;
		//downֵ�ܵ�ǰ���rightֵ���Ҳ���Ƿ�Ϊ�߽�����ϰ���Ӱ��
		if (i+1 == m || table[0][i+1] == 'b') 	info[0][i].down = info[0][i].right;
		else 							   		info[0][i].down = info[0][i].right + 1;
	}
	//step.4------------��ʼ����һ��------------------//
	for (int i=1; i<n; i++)
	{
		//downֵ���Ϸ����downֵ�������Ƿ�Ϊ�ϰ���Ӱ��
		if (table[i][0] == 'b') info[i][0].down =  info[i-1][0].down + 1;
		else 					info[i][0].down =  info[i-1][0].down;
		//rightֵ�ܵ�ǰ���downֵ���·���Ϊ��Ϊ�߽�����ϰ���Ӱ��
		if (i+1 == n || table[i+1][0] == 'b') 	info[i][0].right = info[i][0].down;
		else 									info[i][0].right = info[i][0].down + 1;
	}
	//step.5------------���ƣ���ɨ��------------------//
	for (int i=1; i<n; i++)
	{
		for (int j=1; j<m; j++)
		{
			int right1,right2,down1,down2;
			//step.5.1---------�Ϸ���-----------------//
			//downֵ���Ϸ����downֵ�������Ƿ�Ϊ�ϰ���Ӱ��
			if (table[i][j] == 'b') down1 = info[i-1][j].down + 1;
			else  					down1 = info[i-1][j].down;
			//rightֵ�ܵ�ǰ��downֵ���·��Ƿ�Ϊ�߽�����ϰ���Ӱ��
			if (i+1 == n || table[i+1][j] == 'b') 	right1 = down1;
			else  									right1 = down1 + 1;
			//step.5.2---------����-----------------//
			//rightֵ������rightֵ�������Ƿ�Ϊ�ϰ���Ӱ��
			if (table[i][j] == 'b') right2 = info[i][j-1].right + 1;
			else 					right2 = info[i][j-1].right;
			//downֵ�ܵ�ǰ���rightֵ���Ҳ��Ƿ�Ϊ�߽�����ϰ���Ӱ��
			if (j+1 == m || table[i][j+1] == 'b') 	down2 = right2;
			else 									down2 = right2 + 1;
			//step.5.3---------���-------------------//
			info[i][j].down = min(down1, down2);
			info[i][j].right = min(right1,right2);
		}
	}

	//step.6------------����ҷ���--------------------//
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			cout<<min(info[i][j].right,info[i][j].down)<<" ";
		}
		cout<<endl;
	}
	return min(info[n-1][m-1].right,info[n-1][m-1].down);
}

int main()
{
	int n,m;
	cin>>n>>m;
	char table[100][100];
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			cin>>table[i][j];
		}
	}
	
	cout<<DemoDay(table,n,m)<<endl;
	return 0;
}
