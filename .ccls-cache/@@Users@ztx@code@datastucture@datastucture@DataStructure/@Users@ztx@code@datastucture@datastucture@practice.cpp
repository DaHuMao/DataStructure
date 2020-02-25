#pragma once
#include"practice.h"
using namespace std;



   /////    1
   vector<vector<int>> practice::minpath(vector<vector<int>> v)
  {
	int m = v.size();
	if (m == 0) return { {} };
	int n = v[0].size();
	if (n == 0) return { {} };
	vector<vector<int>> ans(m, vector<int>(n, m*n + 1));
	for (int i = 0; i < m; i++)
	{
		for (int j = 1; j < v[i][0] + 1; j++)
			ans[i][j] = 1;
	}

	for (int j = 1; j < n - 1; j++)
	{
		for (int i = 0; i < m; i++)
			for (int k = max(i - v[i][j], 0); k <= min(v[i][j] + i, m - 1); k++)
				ans[k][j] = min(ans[k][j], ans[i][j] + 1);
		for (int i = m - 1; i >= 0; i--)
			for (int k = max(i - v[i][j], 0); k <= min(v[i][j] + i, m - 1); k++)
				ans[k][j] = min(ans[k][j], ans[i][j] + 1);
		for (int i = 0; i < m; i++)
			for (int k = j + 1; k <= v[i][j] + j&&k < n; k++)
				ans[i][k] = min(ans[i][k], ans[i][j] + 1);
	}

	return ans;
   }
	

    ////////    2
	int practice::findMaxSum(vector<int>& v1, vector<int>& v2) {
		if (v1.empty() && v2.empty()) return 0;
		int m = v1.size(), n = v2.size();
		if (m > n) { swap(v1, v2); swap(m, n); }
		vector<vector<int>> dp(m + 2, vector<int>(n + 1, 0));
		for (int i = 2; i < n + 1; i++)
		{
			dp[0][i] = dp[0][i - 2] + v2[i - 1] * v2[i - 2];
			dp[1][i] = i % 2 ? dp[1][i - 1] + v1[0] * v2[i - 1] : dp[0][i];
		}
		if (v1.empty()) return dp[0][n];
		dp[1][1] = v1[0] * v2[0];
		v1.push_back(0);
		for (int i = 2; i < m + 2; i++) {
			dp[i][0] = i % 2 ? dp[i - 1][0] : dp[i - 1][0] + v1[i - 1] * v1[i - 2];
			dp[i][1] = i % 2 ? dp[i - 1][1] + v1[i - 1] * v1[i - 2] : dp[i - 1][1];
			for (int j = 2; j<n + 1; j++) {
				if ((i + j) % 2)
					dp[i][j] = max(v2[j - 1] * v2[j - 2] + dp[i][j - 2], dp[i - 1][j]);
				else
					dp[i][j] = max(v1[i - 1] * v1[i - 2] + dp[i - 1][j], v1[i - 1] * v2[j - 1] + dp[i][j - 1]);

			}
		}
		v1.pop_back();
		return dp[m+1][n];
	}


	///////     3
	string practice::Nfactorial(int n) {
		string s = "1";
		if (n == 1) return s;
		int p = 0;
		for (int i = 2; i <= n; i++) {
			for (int j = 0; j < s.size(); j++) {
				p = (s[j] - '0')*i + p;
				s[j] = p % 10 + '0';
				p /= 10;
			}
			while (p != 0) {
				s += p % 10 + '0';
				p /= 10;
			}
		}
		reverse(s.begin(), s.end());
		return s;
	}


  ////////    4
	string practice::BigNumMultiply(string s1, string s2) {
		reverse(s1.begin(), s1.end());
		reverse(s2.begin(), s2.end());
		int m = s1.size(), n = s2.size();
		string ans = "";
		if (m < n) {
			swap(s1, s2);
			swap(m, n);
		}
		if (n == 0) return s1;
		for (int i = 0; i < n; i++) {
			string s = "";
			int hi = 0;
			for (char& c : s1) {
				hi = (c - '0')*(s2[i] - '0') + hi;
				s += hi % 10 + '0';
				hi /= 10;
			}
			if (hi != 0)
				s += hi + '0';
			hi = 0;
			int j = i;
			for (; j < ans.size(); j++) {
				hi = ans[j] - '0' + s[j - i] - '0' + hi;
				ans[j] = hi % 10 + '0';
				hi /= 10;
				if (j == ans.size() - 1 && hi != 0)
					ans += '0';
			}
			ans += s.substr(j - i);
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}


	////// 5
	struct tree1 {
		int sum;
		int num;
		bool visited;
		vector<int> c;
		tree1() :sum(0), num(1), visited(false) {};
	};
	vector<int> ans;
	vector<tree1> v;
	void dfs(int val) {
		v[val].visited = true;
		for (int& i : v[val].c)
			if (!v[i].visited) {
				dfs(i);
				v[val].num += v[i].num;
				v[val].sum += v[i].sum + v[i].num;
			}
	}
	void dfsAns(int val, int& N) {
		for (int i : v[val].c)
			if (ans[i] == 0) {
				ans[i] = ans[val] + N - 2 * v[i].num;
				dfsAns(i, N);
			}
	}
	vector<int> practice::sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
		if (edges.empty()) return { 0 };
		v.resize(N);
		ans.resize(N);
		vector<int> f(N, N);
		int rot = edges[0][0];
		for (auto& e : edges) {
			v[e[0]].c.emplace_back(e[1]);
			v[e[1]].c.emplace_back(e[0]);
		}
		dfs(rot);
		ans[rot] = v[rot].sum;
		dfsAns(rot, N);
		return ans;
	}