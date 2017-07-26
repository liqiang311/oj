#include <iostream>
using namespace std;

struct Info
{
	int right,down;
};
/////////////////////////////////////////////////////
//
//  table为输入矩阵，存放初始迷宫信息
//  n为行数
//  m为列数
//  返回值为最小变换次数
//
/////////////////////////////////////////////////////
int DemoDay(char table[100][100], int n, int m)
{
	//step.1------------定义结构体--------------------//
	Info info[100][100];
	//step.2------------初始化起点--------------------//
	info[0][0].right = 0;
	//若起点右侧点为障碍，则自动拐弯向下移动
	if (table[0][1] == 'b') info[0][0].down = 0;
	else 					info[0][0].down = 1;
	//step.3------------初始化第一行------------------//
	for (int i=1; i<m; i++)
	{
		//right值受左侧点的right值和自身是否为障碍物影响
		if (table[0][i] == 'b') info[0][i].right = info[0][i-1].right + 1;
		else 					info[0][i].right = info[0][i-1].right;
		//down值受当前点的right值和右侧点是否为边界或者障碍物影响
		if (i+1 == m || table[0][i+1] == 'b') 	info[0][i].down = info[0][i].right;
		else 							   		info[0][i].down = info[0][i].right + 1;
	}
	//step.4------------初始化第一列------------------//
	for (int i=1; i<n; i++)
	{
		//down值受上方点的down值和自身是否为障碍物影响
		if (table[i][0] == 'b') info[i][0].down =  info[i-1][0].down + 1;
		else 					info[i][0].down =  info[i-1][0].down;
		//right值受当前点的down值和下方点为否为边界或者障碍物影响
		if (i+1 == n || table[i+1][0] == 'b') 	info[i][0].right = info[i][0].down;
		else 									info[i][0].right = info[i][0].down + 1;
	}
	//step.5------------递推，行扫描------------------//
	for (int i=1; i<n; i++)
	{
		for (int j=1; j<m; j++)
		{
			int right1,right2,down1,down2;
			//step.5.1---------上方点-----------------//
			//down值受上方点的down值和自身是否为障碍物影响
			if (table[i][j] == 'b') down1 = info[i-1][j].down + 1;
			else  					down1 = info[i-1][j].down;
			//right值受当前的down值和下方是否为边界或者障碍物影响
			if (i+1 == n || table[i+1][j] == 'b') 	right1 = down1;
			else  									right1 = down1 + 1;
			//step.5.2---------左侧点-----------------//
			//right值受左侧点right值和自身是否为障碍物影响
			if (table[i][j] == 'b') right2 = info[i][j-1].right + 1;
			else 					right2 = info[i][j-1].right;
			//down值受当前点的right值和右侧是否为边界或者障碍物影响
			if (j+1 == m || table[i][j+1] == 'b') 	down2 = right2;
			else 									down2 = right2 + 1;
			//step.5.3---------结合-------------------//
			info[i][j].down = min(down1, down2);
			info[i][j].right = min(right1,right2);
		}
	}

	//step.6------------输出且返回--------------------//
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
