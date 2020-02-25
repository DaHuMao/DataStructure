#pragma once
#include<vector>
#include<algorithm>
#include<map>
#include<stack>
#include<iostream>
using namespace std;
class practice
{
public:
	////  1
	////给定一个矩阵V，矩阵内数值代表可以跨越的最大长度，问最少需要多少步可以从左边到最右边，可以从最左边的任意一点出发；
	vector<vector<int>> minpath(vector<vector<int>> v);	

	////  2
   /////给定两个长度相加为偶数的数组，将他们合并成一个大数组，要求各数组内元素相对顺序不变，
   //////将大数组的每个奇数位于后面的偶数位数字相乘再把所有的积相加，问能得到的最大和是多少。
	int findMaxSum(vector<int>& v1, vector<int>& v2);

	/////  3
	/////  给定一个数N，计算N的阶乘，由于N可能很大，计算机不能直接计算，返回字符串；
	string Nfactorial(int n);

	///// 4
	///// 大数相乘，输入两个纯粹数字组成的字符串，返回他们的乘积（用字符串表示）；
	string BigNumMultiply(string s1, string s2);
	
	//// 5
	//// 求一个二维数组中每一个数与其他数的距离
	vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges);
};


class tree
{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}

	};
	void preorder(TreeNode* p)
	{
		stack<TreeNode*> s;
		while (true)
		{
			while (p)
			{
				s.push(p);
				cout << p->val << " ";
				p = p->left;
			}
			if (s.empty()) break;
			p = s.top();
			s.pop();
			p = p->right;
		}
	}
	void midorder(TreeNode* p)
	{
		stack<TreeNode*> s;
		while (true)
		{
			while (p)
			{
				s.push(p);
				p = p->left;
			}

			if (s.empty()) break;
			p = s.top();
			cout << p->val << " ";
			s.pop();
			p = p->right;
		}

	}
	void postorder(TreeNode* p)
	{
		if (!p) return;
		TreeNode* pre = NULL;
		stack<TreeNode*> s;
		while (true)
		{
			while (p && (p != pre))
			{
				while (p)
				{
					s.push(p);
					p = p->left;
				}
				p = s.top();
				p = p->right;
			}
			pre = s.top();
			cout << pre->val << " ";
			s.pop();
			if (s.empty()) break;
			p = s.top()->right;
		}

	}

	void morrisTraverse_pre(TreeNode* p)
	{
		TreeNode* cur = p;
		TreeNode* pre = NULL;
		while (cur)
		{
			pre = cur->left;
			if (pre)
			{
				while (pre->right&&pre->right != cur)
					pre = pre->right;
				if (pre->right)
					pre->right = NULL;
				else
				{
					pre->right = cur;
					cout << cur->val << " ";
					cur = cur->left;
					continue;
				}
			}
			else
				cout << cur->val << " ";
			cur = cur->right;
		}
		cout << endl;
	}
	void morrisTraverse_mid(TreeNode* p)
	{
		TreeNode* cur = p;
		TreeNode* pre = NULL;
		while (cur)
		{
			pre = cur->left;
			if (pre)
			{
				while (pre->right&&pre->right != cur)
					pre = pre->right;
				if (pre->right)
					pre->right = NULL;
				else
				{
					pre->right = cur;
					cur = cur->left;
					continue;
				}
			}
			cout << cur->val << " ";
			cur = cur->right;
		}
		cout << endl;
	}
	///////////////////
	void reverseTree(TreeNode** p)
	{
		TreeNode* pre = *p;
		TreeNode* cur = (*p)->right;
		while (cur)
		{
			TreeNode* temp = cur->right;
			cur->right = pre;
			pre = cur;
			cur = temp;
		}
		(*p)->right = NULL;
		*p = pre;
	}
	void morrisTraverse_post(TreeNode* p)
	{
		TreeNode* cur = p;
		TreeNode* pre = NULL;
		while (cur)
		{
			pre = cur->left;
			if (pre)
			{
				while (pre->right&&pre->right != cur)
					pre = pre->right;
				if (pre->right)
				{
					pre->right = NULL;
					print(cur->left);
				}
				else
				{
					pre->right = cur;
					cur = cur->left;
					continue;
				}
			}
			cur = cur->right;
		}
		print(p);
		cout << endl;
	}
	void print(TreeNode* p)
	{
		reverseTree(&p);
		TreeNode* temp = p;
		while (temp)
		{
			cout << temp->val << " ";
			temp = temp->right;
		}
		reverseTree(&p);
	}

	//////////////////////////////
	TreeNode* reConstructTree(vector<int> pre, vector<int> vin)
	{
		int len = pre.size() - 1;
		return recreat(pre, vin, 0, len + 1, len);

	}
	TreeNode* recreat(const vector<int> post, const vector<int> mid, int start, int end, int& pos)
	{
		TreeNode* p = NULL;
		for (int i = start; i < end; i++)
		{
			if (mid[i] == post[pos])
			{
				p = (TreeNode*)malloc(sizeof(TreeNode));
				p->val = mid[i];
				pos--;
				p->right = recreat(post, mid, i + 1, end, pos);
				p->left = recreat(post, mid, start, i, pos);
				break;
			}
		}
		return p;
	}



	/////////////////////////////////////////////////////////
	//(1)
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		int l = 0;
		TreeNode* p = rootCreat(pre, l, vin, 0, vin.size());
		return p;
	}
	TreeNode* rootCreat(vector<int> pre, int &startpre, vector<int> vin, int startin, int endin)
	{
		if (startin == endin)
			return NULL;
		TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
		for (int i = startin; i < endin; i++)
		{
			if (pre[startpre] == vin[i])
			{
				root->val = vin[i];
				startpre++;
				root->left = rootCreat(pre, startpre, vin, startin, i);
				root->right = rootCreat(pre, startpre, vin, i + 1, endin);
				break;
			}
		}
		return root;
	}
	bool Tree_ancestor_help(TreeNode* _root, TreeNode*& first, TreeNode*& second, TreeNode*& ans, bool& test1, bool& test2)
	{
		if (!_root || (test1&&test2)) return false;
		if (_root == first)   test1 = true;
		if (_root == second)  test2 = true;
		bool t1 = Tree_ancestor_help(_root->left, first, second, ans, test1, test2);
		bool t2 = Tree_ancestor_help(_root->right, first, second, ans, test1, test2);
		if (t1&&t2) ans = _root;
		if ((_root == first || _root == second) && (t1 || t2)) ans = _root;
		if ((_root == first || _root == second) || (t1 || t2))  return true;
		return false;
	}
	TreeNode* Tree_ancestor(TreeNode* _root, TreeNode* first, TreeNode* second)
	{
		if (!first || !second) return NULL;
		TreeNode* ans = NULL;
		bool test1 = false, test2 = false;
		Tree_ancestor_help(_root, first, second, ans, test1, test2);
		return ans;
	}
};