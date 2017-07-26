#include <iostream>
#include <memory.h>
using namespace std;

#define DIM	50

//�������ѣ��������� 
void ForwardDFS(char map[DIM][DIM],//������� 
				bool sign[DIM][DIM],//���ر�ǽ��ͼ��true��ʾ���Ե�������㣬false��ʾ���ܵ��� 
				int Row,int Col,//�����ģ 
				int curR, int curC)//��ǰ�� 
{
	//�� ��ǰ�����߹� �� ��ǰ�����ϰ��ֹͣ�ݹ� 
	if (sign[curR][curC] || map[curR][curC] == '#')
	{
		return ;
	}
	//��Ǵ˵�ɴ� 
	sign[curR][curC] = true;
	//��ǿ������ĸ������ƶ�
	bool up,down,left,right;
	up = down = left = right = false; 
	if (map[curR][curC] == '.')//�����ƶ� 
	{
		down = true;
	}
	else if (map[curR][curC] == '-')//�����ƶ� 
	{
		left = right = true;
	}
	else if (map[curR][curC] == '|')//�����ƶ� 
	{
		up = down = true;
	}
	else if (map[curR][curC] == '+' || map[curR][curC] == 'S' || map[curR][curC] == 'T')//���������ƶ� 
	{
		up = down = left = right = true;
	}
	//��
	if (up && curR-1 >= 0)
	{
		ForwardDFS(map,sign,Row,Col,curR-1,curC);
	}
	//�� 
	if (down && curR+1 < Row)
	{
		ForwardDFS(map,sign,Row,Col,curR+1,curC);
	}
	//��
	if (left && curC-1 >= 0)
	{
		ForwardDFS(map,sign,Row,Col,curR,curC-1);
	}
	//��
	if (right && curC+1 < Col)
	{
		ForwardDFS(map,sign,Row,Col,curR,curC+1);
	}
}

//���յ����������DFS 
void ReserveDFS(char map[DIM][DIM],//������� 
				bool sign[DIM][DIM],//���ر�ǽ��ͼ��true��ʾ���Ե�������㣬false��ʾ���ܵ��� 
				int Row,int Col,//�����ģ 
				int curR, int curC,//��ǰ�� 
				int preR, int preC)//��һ���� 
{
	//�� ��ǰ�����߹� �� ��ǰ�����ϰ��ֹͣ�ݹ� 
	if (sign[curR][curC] || map[curR][curC] == '#')
	{
		return ;
	}
	//���������ģ����Է���ȥ���������������޷�ԭ·����
	if (map[curR][curC] == '.' && preR == curR+1 && preC == curC)
	{	
		sign[curR][curC] = true;
	}
	//���������Ŀ��Է���ȥ
	else if (map[curR][curC] == '-' && preR == curR)
	{	
		sign[curR][curC] = true;
	}
	//����������� 
	else if (map[curR][curC] == '|' && preC == curC)
	{
		sign[curR][curC] = true;
	}
	//����㷵�� 
	else if (map[curR][curC] == 'S' || map[curR][curC] == '+' || map[curR][curC] == 'T')
	{
		sign[curR][curC] = true;
	}
	//���ɴ���� 
	if (sign[curR][curC] == false)
	{
		return ;
	}
	//��
	if (curR-1 >= 0)
	{
		ReserveDFS(map,sign,Row,Col,curR-1,curC,curR,curC);
	}
	//��
	if (curR+1 < Row)
	{
		ReserveDFS(map,sign,Row,Col,curR+1,curC,curR,curC);
	}
	//��
	if (curC-1 >= 0)
	{
		ReserveDFS(map,sign,Row,Col,curR,curC-1,curR,curC);
	}
	//��
	if (curC+1 < Col)
	{
		ReserveDFS(map,sign,Row,Col,curR,curC+1,curR,curC);
	}
}


int main()
{
	int R,C;
	cin>>R>>C;
	char map[DIM][DIM];
	bool sCanReach[DIM][DIM];//����ܵ���ľ��� 
	bool tCanReach[DIM][DIM];//�յ��ܵ��ľ���  
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			cin>>map[i][j];
		}
	}
	memset(sCanReach,0,DIM*DIM);
	memset(tCanReach,0,DIM*DIM);
	//����
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			if (map[i][j] == 'S')
			{
				ForwardDFS(map,sCanReach,R,C,i,j);
			}
		}
	}
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			if (map[i][j] == 'T')
			{
				if (sCanReach[i][j] == false)
				{
					cout<<"I'm stuck!"<<endl;
					return 0;
				}
				ReserveDFS(map,tCanReach,R,C,i,j,i,j);
			}
		}
	}
	
	int num = 0;

/*	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			cout<<map[i][j]<<" ";
		}
		cout<<endl;
	}
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			cout<<sCanReach[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			cout<<tCanReach[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
*/
	for (int i=0; i<R; i++)
	{
		for (int j=0; j<C; j++)
		{
			if (map[i][j] != 'S' && map[i][j] != 'T' &&
				sCanReach[i][j]  && !tCanReach[i][j])
			{
				num++; 
			}
		}
	}
	cout<<num<<endl;
	return 0;
}
