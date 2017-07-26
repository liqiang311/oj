#include <iostream>
using namespace std;

int main()
{
	int rectNum;
	int rect[1000];
	cin>>rectNum;
	for (int i=0; i<rectNum; i++)
		cin>>rect[i];

// 	int rectNum = 6;
// 	int rect[6] = {3,1,6,5,2,3};
	int maxArea = 0;
	for (int i=0; i<rectNum; i++)
	{
		int minHeight = rect[i];
		maxArea = max(maxArea, minHeight);
		for (int j=i+1; j<rectNum; j++)
		{
			//i到j的最小值
			minHeight = min(minHeight, rect[j]);
			maxArea = max(maxArea, minHeight*(j-i+1));
		}
	}
	cout<<maxArea<<endl;
	return 0;
}