#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;


//此题目为求树的直径
//方法为2次dfs,任一点求一个最远点,一定是两个点中其一
//再从这点dfs,求到最远的点即为所求
struct Node
{
	int parent;//父亲节点 
	int stage;
	Node(int p,int s)
	{
		parent = p;
		stage = s;
	}
};
int DisOf2Node(vector<Node> &tree,int node1,int node2)
{
	int dis = 0;
	//先看两个node的级别相同否,若不相同,则大的向小的靠拢
	if (tree[node1].stage > tree[node2].stage)
	{
		while (tree[node1].stage != tree[node2].stage)
		{
			node1 = tree[node1].parent;
			dis ++;
		}
	}
	else if (tree[node1].stage < tree[node2].stage)
	{
		while (tree[node1].stage != tree[node2].stage)
		{
			node2 = tree[node2].parent;
			dis ++;
		}
	}
	//此时等级相同,同时往上寻找,直到相同
	while(node1 != node2)
	{
		node1 = tree[node1].parent;
		node2 = tree[node2].parent;
		dis += 2;
	} 
	return dis;
}

int main()
{
	int n,m;
	cin>>n>>m;
	vector<Node> tree;
	tree.push_back(Node(-1,0));
	for (int i=0; i<n-1+m; i++)
	{
		int tmp;
		cin>>tmp;
		tmp--;
		tree.push_back(Node(tmp,tree[tmp].stage+1));
	}
	//从根节点找一个最远的,即层数最高的 
	int maxStage=0,NodeA;
	for (int i=0; i<tree.size(); i++)
	{
		if (tree[i].stage > maxStage)
		{
			maxStage = tree[i].stage;
			NodeA = i;
		}
	}
	//从NodeA出发找到的最远的点即为树的直径 
	int maxDis = 0;
	for (int i=0; i<tree.size(); i++)
	{
		maxDis = max(maxDis,DisOf2Node(tree,NodeA,i));
	}
	cout<<maxDis<<endl;
	return 0;	
} 






/*
交换机为树,其中交换机的一个属性为是否拥有电脑 


struct Node
{
	int parent;//父亲节点 
	int stage;
	bool isHave;//是否拥有电脑 
	Node()
	{
		parent = 0;
		stage = 0;
		isHave = false;
	}
};

int DisOf2Node(vector<Node> &tree,int node1,int node2)
{
	int dis = 0;
	if (tree[node1].isHave) dis++;
	if (tree[node2].isHave) dis++;
	//先看两个node的级别相同否,若不相同,则大的向小的靠拢
	if (tree[node1].stage > tree[node2].stage)
	{
		while (tree[node1].stage != tree[node2].stage)
		{
			node1 = tree[node1].parent;
			dis ++;
		}
	}
	else if (tree[node1].stage < tree[node2].stage)
	{
		while (tree[node1].stage != tree[node2].stage)
		{
			node2 = tree[node2].parent;
			dis ++;
		}
	}
	//此时等级相同,同时往上寻找,知道相同
	while(node1 != node2)
	{
		node1 = tree[node1].parent;
		node2 = tree[node2].parent;
		dis += 2;
	} 
	return dis;
}

int main()
{
	int n,m;
	cin>>n>>m;
	//第一台交换机
	vector<Node> tree;
	Node node;
	node.parent = -1;
	tree.push_back(node);
	for (int i=1; i<=n-1; i++)
	{
		//录入新节点 
		Node node;
		cin>>node.parent;
		node.parent -= 1;
		node.stage = tree[node.parent].stage+1;
		tree.push_back(node);
	}
	for (int i=0; i<m; i++)
	{
		int tmp;
		cin>>tmp;
		tmp -= 1;
		tree[tmp].isHave = true;
	}
	int maxDis = 0;
	char *isProc=new char[tree.size()];
	for (int i=tree.size()-1; i>=0; i--)
	{
		memset(isProc,0,tree.size());
		for (int j=i-1; j>=0; j--)
		{
			if (isProc[j]) continue;
			if (2+tree[i].stage+tree[j].stage <= maxDis) continue;
			maxDis = max(maxDis, DisOf2Node(tree,i,j));
			//j的所有父亲全部算错处理过
			isProc[j] = 1;
			int k=j;
			while (k>=0)
			{
				isProc[k] = 1;
				k = tree[k].parent;
			}
		}
		int tmpDis = 0;
		if (tree[i].isHave) tmpDis++;
		if (tree[0].isHave) tmpDis++;
		tmpDis += tree[i].stage;
		maxDis = max(tmpDis,maxDis);
	}
	cout<<maxDis<<endl;
	return 0;
}

*/
