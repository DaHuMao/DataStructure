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
	////����һ������V����������ֵ������Կ�Խ����󳤶ȣ���������Ҫ���ٲ����Դ���ߵ����ұߣ����Դ�����ߵ�����һ�������
	vector<vector<int>> minpath(vector<vector<int>> v);	

	////  2
   /////���������������Ϊż�������飬�����Ǻϲ���һ�������飬Ҫ���������Ԫ�����˳�򲻱䣬
   //////���������ÿ������λ�ں����ż��λ��������ٰ����еĻ���ӣ����ܵõ��������Ƕ��١�
	int findMaxSum(vector<int>& v1, vector<int>& v2);

	/////  3
	/////  ����һ����N������N�Ľ׳ˣ�����N���ܴܺ󣬼��������ֱ�Ӽ��㣬�����ַ�����
	string Nfactorial(int n);

	///// 4
	///// ������ˣ�������������������ɵ��ַ������������ǵĳ˻������ַ�����ʾ����
	string BigNumMultiply(string s1, string s2);
	
	//// 5
	//// ��һ����ά������ÿһ�������������ľ���
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