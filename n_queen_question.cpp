#include <stdio.h>

/*
 *	1阶问题唯一解
 *	2阶问题3阶问题无解
 *	4阶问题唯一真实解
 */
void NQueensProblemFor4()
{
	
	int r1,r2,r3,r4;//分别表示每个皇后摆放的行数，一列放一个，第一个在第一列r1行，第二个在第二列r2行
	for (r1=1; r1<=4; r1++)
	{
		for (r2=1; r2<=4; r2++)
		{
			if (r2==r1 || r2+1==r1 || r2-1==r1)//no same row and same diagonal
				continue;
			for (r3=1; r3<=4; r3++)
			{
				if (r3==r2 || r3==r1 || r3+1==r2 || r3-1==r2 || r3+2==r1 || r3-2==r1)
					continue;
				for (r4=1; r4<=4; r4++)
				{
					if (r4==r3 || r4==r2 || r4==r1 || r4+1==r3 || r4-1==r3 || r4+2==r2 || r4-2==r2 || r4+3==r1 || r4-3==r1)
						continue;
					printf("%d %d %d %d \n",r1,r2,r3,r4);
				}
			}
		}
	}
}

int main()
{
	NQueensProblemFor4();
	getchar();

	return 0;
}

