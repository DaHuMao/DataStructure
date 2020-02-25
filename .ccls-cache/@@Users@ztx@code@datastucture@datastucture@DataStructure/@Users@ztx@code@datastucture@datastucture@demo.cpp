#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<functional>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<stdio.h>
#include"order.h"
#include"RBTree.hpp"
#include"practice.h"
#include"mylist.h"
#include<string>
#include<bitset>
#include"left_heap.h"
#include<time.h>
#include<fstream>
#include <iterator> 
#include<list>
#include<sstream>
using namespace std;

void test(int num) {
time_t rawtime;
time(&rawtime);
struct tm * ti = localtime(&rawtime);

int v[10000];

RBTree<int> t;
multiset<int> s;
int time1 = ti->tm_min * 60 + ti->tm_sec;
cout << "RBtree开始插入数据，当前时间:" << time1 << "秒" << endl;

for (int i = 0; i < num; i++) {
	int a = rand() % INT_MAX;
	t.insert(a);
	//s.insert(a);
}
time(&rawtime);
ti = localtime(&rawtime);
cout << "插入完成，当前时间：" << ti->tm_min * 60 + ti->tm_sec << "，RBtree用时："
<< ti->tm_min * 60 + ti->tm_sec - time1 << "秒" << endl;
time1 = ti->tm_min * 60 + ti->tm_sec;
time(&rawtime);
ti = localtime(&rawtime);
cout << "set开始插入数据，当前时间:" << time1 << "秒" << endl;
for (int i = 0; i < num; i++) {
	int a = rand() % INT_MAX;
	s.insert(a);
}
time(&rawtime);
ti = localtime(&rawtime);

cout << "插入完成，当前时间：" << ti->tm_min * 60 + ti->tm_sec << "，set用时："
<< ti->tm_min * 60 + ti->tm_sec - time1 << "秒" << endl;
//t.mid_traverse();
auto it1 = t.begin();
auto it2 = s.begin();
time1 = ti->tm_min * 60 + ti->tm_sec;
cout << "rbtree开始删除,time: " <<time1<< endl;
while (it1 != t.end()) {
	t.erase(it1++);
}
time(&rawtime);
ti = localtime(&rawtime);
if (it1 == t.end()) {
	cout << "rbtree删除完成，用时：" << ti->tm_min * 60 + ti->tm_sec - time1 << endl;
}
time1 = ti->tm_min * 60 + ti->tm_sec;
cout << "set开始删除, time:" <<time1<< endl;
while (it2 != s.end()) {
	s.erase(it2++);
}
cout << endl;
time(&rawtime);
ti = localtime(&rawtime);
if (it2 == s.end()) {
	cout << "set删除完成，用时：" << ti->tm_min * 60 + ti->tm_sec - time1 << endl;
}
int cnt = 0;
}















class mypriority_queue {
public:
	mypriority_queue(size_t maxsize);
	void push(const pair<int, int>& val);
	void pop();
	pair<int, int> top();
	void change(int index, int val);//表示要将数组位置在index的数改成val
	bool empty();
private:
	//上虑的过程
	void up_adjust(int index);

	//下虑的过程
	void down_adjust(int index, int bound);

	//存储堆的数组，pair第一个参数是value，第二个参数是该value在原来的数组中的位置
	vector<pair<int, int>> v;

	//是数组原来位置的下标对应的我们堆里面的下标 比如有个数1是存储在外面的数组Vtemp[2]中，但在堆中的位置是第八个数，也就是v[8],
	//那么数组v[8]里存储（1,2），表示数1在外面数组的位置是2，而Vindex[2]=8,表示外面第二个位置的数在堆中是第八个位置
	vector<int> vIndex;
	int size;
};
mypriority_queue::mypriority_queue(size_t maxsize) :v(maxsize), vIndex(maxsize), size(0) {};
void mypriority_queue::push(const pair<int, int>& val) {
	++size;
	v[size] = val;
	vIndex[val.second] = size;
	up_adjust(size);
};
void mypriority_queue::pop() {
	swap(v[1], v[size]);
	swap(vIndex[v[1].second], vIndex[v[size].second]);
	--size;
	down_adjust(1, size);
};
pair<int, int> mypriority_queue::top() {
	if (size == 0) throw;
	return v[1];
};
void mypriority_queue::change(int index, int val) {
	int old = v[vIndex[index]].first;
	v[vIndex[index]].first = val;
	if (old < val)
		up_adjust(vIndex[index]);
	else
		down_adjust(vIndex[index], size);
};
bool mypriority_queue::empty() {
	return size == 0;
};

void mypriority_queue::up_adjust(int index) {
	int pindex = index / 2;
	if (pindex > 0 && v[index] > v[pindex]) {
		swap(v[pindex], v[index]);
		swap(vIndex[v[pindex].second], vIndex[v[index].second]);
		up_adjust(pindex);
	}
};
void mypriority_queue::down_adjust(int index, int bound) {
	int l = 2 * index;
	int r = l + 1;
	int tar = index;
	if (l <= bound&&v[l] > v[tar]) tar = l;
	if (r <= bound&&v[r] > v[tar]) tar = r;
	if (tar != index) {
		swap(v[tar], v[index]);
		swap(vIndex[v[tar].second], vIndex[v[index].second]);
		down_adjust(tar, bound);
	}

};





int main()
{
	test(5000000);
	vector<vector<int>> v = { {1,2,3},{2,3,4} };
	segTree1<vector<int>,int> seg1(v);
	cout<< seg1.sum(vector<int>{0,0}, vector<int>{1,2})<<" ";
	seg1.update(vector<int>{0,1}, 9);
	cout<<seg1.sum(vector<int>{0,0}, vector<int>{1,1})<<" ";
	return 0;
}












struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}	
};
class Solution1224 {
public:
	TreeNode *sortedListToBST(ListNode *head) {
		if (!head) return NULL;
		return sortedListToBSThelp(head, NULL);
	}
	TreeNode *sortedListToBSThelp(ListNode *head, ListNode *end) {
		if (head == end) return NULL;
		ListNode* mid = findMid(head, end);
		TreeNode* root = new TreeNode(mid->val);
		root->left = sortedListToBSThelp(head, mid);
		root->right = sortedListToBSThelp(mid->next, end);
		return root;
	}
	ListNode* findMid(ListNode *head, ListNode* end) {
		ListNode* fast = head->next;
		ListNode* slow = head;
		while (fast != end&&fast->next != end) {
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}
};




	





class LFUCache {
public:
	struct node {
		int key, val, count;;
		node* next;
		node* front;
		node() :key(0), val(0), count(0),next(NULL),front(NULL) {};
	};
	LFUCache(int capacity) {
		maxsize = capacity;
		head = new node();
		tail = new node();
		head->next = tail;
		tail->front = head;
		mcount[0] = head;
	}

	int get(int key) {
		if (!mkey.count(key)) return -1;
		visied(mkey[key]);
		printf();
		return mkey[key].val;
	}

	void put(int key, int value) {
		if (mkey.size() == maxsize)
			pop();
		mkey[key].key = key;
		mkey[key].val = value;
		visied(mkey[key]);		
		printf();
	}
	void visied(node& n) {
		if (n.front)
			n.front->next = n.next;
		if (n.next)
			n.next->front = n.front;
		++n.count;
		if (&n == mcount[n.count - 1])
			mcount[n.count - 1] = n.front;
		node* temp = NULL;
		if (mcount[n.count] != NULL)
			temp = mcount[n.count];
		else
			temp = mcount[n.count - 1];
		temp->next->front = &n;
		n.next = temp->next;
		temp->next = &n;
		n.front = temp;
		mcount[n.count] = &n;
		if (mcount[n.count - 1]->count != n.count - 1) mcount[n.count - 1] = NULL;
	}
	void pop() {
		node* temp = head->next;
		head->next = temp->next;
		temp->next->front = head;
		if (temp->count != head->next->count)
			mcount[temp->count] = NULL;
		mkey.erase(temp->key);
	}
	void printf() {
		node* p = head;
		while (p) {
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
		p = tail;
		while (p) {
			cout << p->val << " ";
			p = p->front;
		}
		cout << endl << endl;
	}
private:
	unordered_map<int, node*> mcount;
	unordered_map<int, node> mkey;
	node* head;
	node* tail;
	int maxsize;
};




class LRUCache {
public:
	struct node {
		int key;
		int val;
		node* front;
		node* next;
		node() : val(0), front(NULL), next(NULL) {};
		node(int value, int Key) :val(value), key(Key), front(NULL), next(NULL) {};
	};
	LRUCache(int capacity) {
		maxsize = capacity;
		head = new node();
		tail = new node();
		head->next = tail;
		tail->front = head;
	}

	int get(int key) {
		if (!m.count(key) || maxsize == 0) return -1;
		node& n = m[key];
		visied(n);
		return n.val;
	}

	void put(int key, int value) {
		if (maxsize == 0)  return;
	
		m[key].val = value;
		m[key].key = key;
		visied(m[key]);
		if (m.size()>maxsize)
			pop();
	}
	void visied(node& n) {
		if (n.front)
			n.front->next = n.next;
		if (n.next)
			n.next->front = n.front;
		n.next = head->next;
		head->next->front = &n;
		head->next = &n;
		n.front = head;
	}
	void pop() {
		node* temp = tail->front;
		tail->front = temp->front;
		temp->front->next = tail;
		m.erase(temp->key);
	}
private:
	int size;
	int maxsize;
	node* head;
	node* tail;
	unordered_map<int, node> m;
};

