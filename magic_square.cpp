#include <stdio.h>
//穷举法and回溯法求3阶幻方
//循环中的各个判断即为回溯条件
//在不知道幻方的具体属性时
bool IsEqual(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8)
{
	if (a1==a2 && a3==a4 && a5==a6 && a7==a8)
		if (a1==a3 && a5==a7)
			if (a1==a5)
				return true;
	return false;
}
void MagicSquare3ByExhaust()
{
	int R[1000][9];
	int count=0;
	int r1,r2,r3,r4,r5,r6,r7,r8,r9;
	//如何快速获取1-9的全排列？这里采用最笨的办法
	for (r1=1; r1<=9; r1++)
	{
		for (r2=1; r2<=9; r2++)
		{
			if (r2==r1)
				continue;
			for (r3=1; r3<=9; r3++)
			{
				if (r3==r2 || r3==r1)
					continue;
				for (r4=1; r4<=9; r4++)
				{
					if (r4==r3 || r4==r2 || r4==r1)
						continue;
					for (r5=1; r5<=9; r5++)
					{
						if (r5==r4 || r5==r3 || r5==r2 || r5==r1)
							continue;
						for (r6=1; r6<=9; r6++)
						{
							if (r6==r5|| r6==r4 || r6==r3 || r6==r2 || r6==r1)
								continue;
							for (r7=1; r7<=9; r7++)
							{
								if (r7==r6 || r7==r5 || r7==r4 || r7==r3 || r7==r2 || r7==r1)
									continue;
								for (r8=1; r8<=9; r8++)
								{
									if (r8==r7 || r8==r6 || r8==r5 || r8==r4 || r8==r3 || r8==r2 || r8==r1)
										continue;
									r9=1+2+3+4+5+6+7+8+9-r1-r2-r3-r4-r5-r6-r7-r8;
									//if (r1+r2+r3==r4+r5+r6==r7+r8+r9==r1+r4+r7==r2+r5+r8==r3+r6+r9==r1+r5+r9==r3+r5+r7)
									//错误 数字不能连等，因为int和int先判断相等后返回bool型
									if(IsEqual(r1+r2+r3,r4+r5+r6,r7+r8+r9,r1+r4+r7,r2+r5+r8,r3+r6+r9,r1+r5+r9,r3+r5+r7))
									{
										R[count][0]=r1; R[count][1]=r2; R[count][2]=r3; R[count][3]=r4; R[count][4]=r5;
										R[count][5]=r6; R[count][6]=r7; R[count][7]=r8; R[count][8]=r9;
										count++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	//输出结果到屏幕
	for (int i=0; i<count; i++)
	{
		printf("%d %d %d\n%d %d %d\n%d %d %d\n\n",
				R[i][0],R[i][1],R[i][2],R[i][3],R[i][4],R[i][5],R[i][6],R[i][7],R[i][8]);
	}
	printf("共%d种.\n",count);
}

int main()
{
	MagicSquare3ByExhaust();
	getchar();
	return 0;
}