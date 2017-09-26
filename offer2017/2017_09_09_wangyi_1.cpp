#include <iostream>
#include <vector>
using namespace std;

bool dfs(vector<int> &arr, vector<bool> &v, int cur, vector< vector<bool> > &mul)
{
	bool isEnd = true;
	for (int i = 0; i < v.size(); i++)
		if (!v[i]) {
			isEnd = false;
			break;
		}
	if (isEnd) return true;

	for (int i = 0; i < arr.size(); i++)
	{
		if (!v[i])
		{
			if (mul[cur][i])
			{
				v[i] = true;
				if (dfs(arr, v, i, mul)) return true;
				v[i] = false;
			}
		}
	}
	return false;
}

bool IsOk(vector<int> arr, vector< vector<bool> > &mul)
{
	for (int i = 0; i < arr.size(); i++)
	{
		vector<bool> v;
		for (int i = 0; i < arr.size(); i++)
			v.push_back(false);
		v[i] = true;

		if (dfs(arr, v, i, mul)) return true;

		v[i] = false;
	}

	return false;
}

int main()
{
	int t;
	cin >> t;
	vector< vector<int> > arr;
	arr.resize(t);

	for (int i = 0; i < t; i++)
	{
		int n;
		cin >> n;
		arr[i].resize(n);
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];
	}

	for (int i = 0; i < t; i++)
	{
		vector< vector<bool> > mul;
		mul.resize(arr[i].size());
		for (int k = 0; k < arr[i].size(); k++)
			mul[k].resize(arr[i].size());
		for (int k = 0; k < arr[i].size(); k++)
		{
			for (int j = k + 1; j < arr[i].size(); j++)
			{
				long long temp = arr[i][k] * arr[i][j];
				if (temp % 4 == 0) mul[k][j] = mul[j][k] = true;
				else mul[k][j] = mul[j][k] = false;
			}
		}

		if (IsOk(arr[i], mul)) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
}

/*
2
3
1 10 100
4
1 2 3 4

*/
