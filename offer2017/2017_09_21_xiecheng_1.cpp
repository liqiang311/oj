#include <iostream>
#include <vector>
#include <stack>

using namespace std;

#define max(a,b) (a>b?a:b)

int fun1(vector< vector<int> > &arr, int ii, int jj)
{
	vector< vector<int> > f;
	f.resize(arr.size());
	for (int i = 0; i < f.size(); i++)
	{
		f[i].resize(arr[i].size());
		for (int j = 0; j < arr[i].size(); j++)
		{
			f[i][j] = 0;
		}
	}
	f[ii][jj] = 1;
	stack<pair<int, int>> s;
	s.push(pair<int, int>(ii, jj));
	while (!s.empty())
	{
		pair<int, int>  p = s.top();
		s.pop();

		int ff = p.first, ss = p.second, newv = f[p.first][p.second] + 1;

		if (ff - 1 >= 0 && arr[ff][ss] > arr[ff - 1][ss] && newv > f[ff - 1][ss])
		{
			f[ff - 1][ss] = newv;
			s.push(pair<int, int>(ff - 1, ss));
		}
		if (ff + 1 < arr.size() && arr[ff][ss] > arr[ff + 1][ss] && newv > f[ff + 1][ss])
		{
			f[ff + 1][ss] = newv;
			s.push(pair<int, int>(p.first + 1, p.second));
		}
		if (ss - 1 >= 0 && arr[ff][ss] > arr[ff][ss - 1] && newv > f[ff][ss-1])
		{
			f[ff][ss - 1] = newv;
			s.push(pair<int, int>(ff, ss - 1));
		}
		if (ss + 1 < arr.size() && arr[ff][ss] > arr[ff][ss + 1] && newv > f[ff][ss + 1])
		{
			f[ff][ss + 1] = newv;
			s.push(pair<int, int>(p.first, p.second + 1));
		}
	}

	int res = 0;
	for (int i = 0; i < f.size(); i++)
	{
		for (int j = 0; j < arr[i].size(); j++)
		{
			if (f[i][j] > res) res = f[i][j];
		}
	}
	return res;
}

int fun(vector< vector<int> > arr)
{
	int res = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[i].size(); j++)
		{
			int res1 = fun1(arr, i, j);
			if (res1 > res) res = res1;
		}
	}
	return res;
}

int main()
{
	int X, Y;
	while (cin >> X && cin >> Y)
	{
		vector<vector<int> > vec(X, vector<int>(Y, 0));
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				cin >> vec[i][j];
			}
		}
		cout << fun(vec) << endl;
	}
	return 0;
}


/*
2 2
3 2
1 3
4 4
1 2 3 4
12 13 14 5
11 16 15 6
10 9 8 7
*/
