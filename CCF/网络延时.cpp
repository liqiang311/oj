#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;


//����ĿΪ������ֱ��
//����Ϊ2��dfs,��һ����һ����Զ��,һ��������������һ
//�ٴ����dfs,����Զ�ĵ㼴Ϊ����
struct Node
{
	int parent;//���׽ڵ� 
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
	//�ȿ�����node�ļ�����ͬ��,������ͬ,������С�Ŀ�£
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
	//��ʱ�ȼ���ͬ,ͬʱ����Ѱ��,ֱ����ͬ
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
	//�Ӹ��ڵ���һ����Զ��,��������ߵ� 
	int maxStage=0,NodeA;
	for (int i=0; i<tree.size(); i++)
	{
		if (tree[i].stage > maxStage)
		{
			maxStage = tree[i].stage;
			NodeA = i;
		}
	}
	//��NodeA�����ҵ�����Զ�ĵ㼴Ϊ����ֱ�� 
	int maxDis = 0;
	for (int i=0; i<tree.size(); i++)
	{
		maxDis = max(maxDis,DisOf2Node(tree,NodeA,i));
	}
	cout<<maxDis<<endl;
	return 0;	
} 






/*
������Ϊ��,���н�������һ������Ϊ�Ƿ�ӵ�е��� 


struct Node
{
	int parent;//���׽ڵ� 
	int stage;
	bool isHave;//�Ƿ�ӵ�е��� 
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
	//�ȿ�����node�ļ�����ͬ��,������ͬ,������С�Ŀ�£
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
	//��ʱ�ȼ���ͬ,ͬʱ����Ѱ��,֪����ͬ
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
	//��һ̨������
	vector<Node> tree;
	Node node;
	node.parent = -1;
	tree.push_back(node);
	for (int i=1; i<=n-1; i++)
	{
		//¼���½ڵ� 
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
			//j�����и���ȫ��������
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
