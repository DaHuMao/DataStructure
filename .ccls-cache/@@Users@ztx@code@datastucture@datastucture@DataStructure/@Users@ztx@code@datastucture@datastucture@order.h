#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<random>
#include<queue>
using namespace std;
class myorder
{

public:

	template<typename T>
	void print1( vector<T> &v)
	{
		
		for (int j = 0; j < v.size(); j++)
		{
			cout << v[j] << " ";
		}
		cout << endl;
	}
	template<typename T>
	void print2(const vector<vector<T>> &v)
	{
		for (int i = 0; i < v.size(); i++)
		{
			int size = v[i].size();
			cout << "[";
				for (int j = 0; j<size; j++)
					cout << v[i][j] << " ";
				cout << "]" << endl;;
		}
		cout << endl;
	}
	////快速排序
	void QKsort(vector<int> &v, int lo, int hi)
	{
		if (lo >= hi) return;
		//int pos = numpos(v, lo, hi);
		int temp = v[lo], mid = lo;
		for (int i = lo; i <= hi; i++)
			if (v[i] < temp)
				swap(v[++mid], v[i]);
		swap(v[lo], v[mid]);
		QKsort(v, lo, mid - 1);
		QKsort(v, mid + 1, hi);
	}
	void QKsort2(vector<int> &v)
	{
		if (v.size() < 2) return;
		stack<pair<int, int>> s;
		s.push({ 0, (int)v.size() - 1 });
		while (!s.empty())
		{
			int lo = s.top().first;
			int hi = s.top().second;
			s.pop();
			int mid = numpos(v, lo, hi);
			if (mid - lo > 1)
				s.push({ lo,mid - 1 });
			if (hi - mid > 1)
				s.push({ mid + 1,hi });
		}
	}
	int numpos(vector<int> &v, int lo, int hi)
	{
		swap(v[lo], v[lo+rand() % (hi - lo+1)]);
		int temp = v[lo], mid = lo;
		for (int i = lo; i <= hi; i++)
			if (v[i] < temp)
				swap(v[++mid], v[i]);
		swap(v[lo], v[mid]);
		return mid;
	}
	/////归并排序
	void MERGE_SORT(vector<int> &v,int start,int end)
	{
		if (start == end) return;
		int mid = (start + end) / 2;
		MERGE_SORT(v, start, mid);
		MERGE_SORT(v, mid + 1, end);
		MERGE(v, start, mid, end);
	}
	void MERGE(vector<int> &v, int start, int mid, int end)
	{
		vector<int> v1;
		v1.assign(v.begin(), v.begin() + mid+1);
		int j = mid + 1, i = start,len=start;
		while (i<mid+1)
		{
			if (j>end||v1[i] < v[j])
				v[len++] = v1[i++];
			else 
				v[len++] = v[j++];
		}
	}


//////堆排序
	void MAX_heap(vector<int> &v, int i,int maxindex)
	{
		int L = 2 * i + 1, R = 2 * i + 2;
		int largest = i;
		if (L<maxindex && v[L]>v[largest])
			largest = L;
		if (R<maxindex && v[R]>v[largest])
			largest = R;
		if (largest != i)
		{
			swap(v[i], v[largest]);
			MAX_heap(v, largest,maxindex);
		}

	}
	
	void SORT_heap(vector<int> &v)
	{
		int len = v.size() - 1;
		for (int i = len / 2; i >= 0; i--)
			MAX_heap(v, i, len);
		for (int i = len; i > 0; i--)
		{
			swap(v[0], v[i]);
			MAX_heap(v, 0, i);
		}
	}
/////希尔排序
	void shellsort(vector<int>& a)
	{
		int i, j, gap,n=a.size();

		for (gap = n / 2; gap > 0; gap /= 2)
			for (i = gap; i < n; i++)
				for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
					swap(a[j], a[j + gap]);
	}
/// 基数排序
	void radix_sort(vector<int>& v)
	{
		vector<vector<int>> buk(10, vector<int>());
		int i = 0;
		int size = 0;
		while (size < v.size())
		{
			for (int j = 0; j < v.size(); j++)
			{
				int pos = v[j] /(int)pow(10, i) % 10;
				buk[pos].push_back(v[j]);
			}
			int len = 0;
			size = buk[0].size();
			for (size_t x = 0; x < buk.size(); x++)
			{
				for (int y = 0; y < buk[x].size(); y++)
					v[len++] = buk[x][y];
				if(!buk[x].empty())
				buk[x].clear();
			}
			i++;
		}
	}
};

template<class T, class elem>
class segTree1 {
public:
	segTree1(vector<T>& v1) :ori(v1), node(makeVec(v1)) {
		vector<int> point;
		init(ori, point, 0);
	};
	void update(vector<int> point, elem val) {
		pointChange(point);
		auto val1 = val - assign(ori, point, 0, val, 1);
		treeUpdate(node, point, 0, val1);
	}
	elem sum(vector<int> point1, vector<int> point2) {
		pointChange(point1);
		pointChange(point2);
		return treeSum(node, point1, point2, 0);
	}
	void updateAdd(vector<int> point, elem val) {
		pointChange(point);
		treeUpdate(node, point, 0, val);
		assign(ori, point, 0, val, 2);
	}
private:
	void pointChange(vector<int>& point) {
		for (int& e : point)
			++e;
	}
	template<class vecType>
	vector<vecType> makeVec(vector<vecType>& v) {
		return vector<vecType>(v.size() + 1, makeVec(v[0]));
	}
	elem makeVec(elem& e) {
		return elem();
	}
	template<class vecType>
	void init(vector<vecType>& v, vector<int>& point, int n) {
		if (point.size()<n + 1)
			point.push_back(0);
		for (int i = 0; i < v.size(); ++i) {
			point[n] = i + 1;
			init(v[i], point, n + 1);
		}
	}
	void init(elem& e, vector<int>& point, int n) {
		treeUpdate(node, point, 0, e);
	}
	template<class vecType>
	elem assign(vector<vecType>& v, vector<int>& point, int n, elem& val, int flag) {
		return assign(v[point[n] - 1], point, n + 1, val, flag);
	}
	elem assign(elem& e1, vector<int>& point, int n, elem& val, int flag) {
		auto tmp = e1;
		if (flag == 1)
			e1 = val;
		else if (flag == 2)
			e1 = e1 + val;
		return tmp;
	}
	template<class vectype>
	void treeUpdate(vector<vectype>& v, vector<int>& point, int n, elem& val) {
		int index = point[n];
		while (index < v.size()) {
			treeUpdate(v[index], point, n + 1, val);
			index += index&(-index);
		}
	}
	void treeUpdate(elem& e, vector<int>& point, int n, elem& val) {
		e = e + val;
	}
	template<class vectype>
	elem treeSum(vector<vectype>& v, vector<int>& point1, vector<int>& point2, int n) {
		elem ans = elem();
		int i = max(point1[n], point2[n]), j = min(point1[n], point2[n]) - 1;
		while (i > 0) {
			ans += treeSum(v[i], point1, point2, n + 1);
			i -= i&(-i);
		}
		while (j > 0) {
			ans -= treeSum(v[j], point1, point2, n + 1);
			j -= j&(-j);
		}
		return ans;
	}
	elem treeSum(elem& e, vector<int>& point1, vector<int>& point2, int n) {
		return e;
	}
	vector<T> ori;
	vector<T> node;
};
/*class mypriority_queue {
public:
	mypriority_queue(size_t maxsize);
	void push(const pair<int, int>& val);
	void pop();
	const pair<int, int>& top();
	void change(int index, int val);
	bool empty();
private:
	void up_adjust(int index);
	void down_adjust(int index,int bound);
	void make_heap();

	vector<pair<int, int>> v;
	vector<int> vIndex;
	int size;
};


enum state{visited,inqueue,ori};
struct mapNode {
	mapNode() :p(0), state(ori), minpath(INT_MAX) {};
	void init() {
		p = 0;
		state = (ori);
		minpath = INT_MAX;
	}
	int p;
	state state;
	int minpath;
};
mypriority_queue::mypriority_queue(size_t maxsize) :v(maxsize), vIndex(maxsize), size(0) {};
void mypriority_queue::push(const pair<int, int>& val) {
	++size;
	v[size] = val;
	vIndex[val.second] = size;
	up_adjust(size);
};
void mypriority_queue::pop() {
	v[1] = v[size];
	vIndex[v[1].second] = 1;
	--size;
	down_adjust(1, size);
};
const pair<int, int>& mypriority_queue::top() {
	if (size == 0) throw;
	return v[1];
};
void mypriority_queue::change(int index, int val) {
	int old = v[vIndex[index]].first;
	v[vIndex[index]].first = val;
	if (old > val)
		up_adjust(vIndex[index]);
	else
		down_adjust(vIndex[index], size);
};
bool mypriority_queue::empty() {
	return size == 0;
};

void mypriority_queue::up_adjust(int index) {
	int pindex = index / 2;
	if (pindex > 0 && v[index] < v[pindex]) {
		swap(v[pindex], v[index]);
		swap(vIndex[v[pindex].second], vIndex[v[index].second]);
		up_adjust(pindex);
	}
};
void mypriority_queue::down_adjust(int index, int bound) {
	int l = 2 * index;
	int r = l + 1;
	int tar = index;
	if (l <= bound&&v[l] < v[tar]) tar = l;
	if (r <= bound&&v[r] < v[tar]) tar = r;
	if (tar != index) {
		swap(v[tar], v[index]);
		swap(vIndex[v[tar].second], vIndex[v[index].second]);
		down_adjust(tar, bound);
	}

};
void mypriority_queue::make_heap() {};
class mymap {
public:
	mymap(vector<vector<pair<int, int>>>& m) :_m(m) { v.resize(m.size()); };
	void Prim();
	void Kruskal();
	void oriDijstra(int start, int end);
	void newDijstra(int start, int end);
	void initMap();
private:
	vector<mapNode> v;
	vector<vector<pair<int, int>>>& _m;
	void printPath(int curNode, int& start);
};
void mymap::initMap() {
	for (auto& e : v)
		e.init();
}
struct edg {
	int weight, num, p;
	edg(int x = 0, int y = 0, int z = 0) :weight(x), num(y), p(z) {};
	bool operator<( const edg& oth)const {
		if (weight == oth.weight)
			return num > oth.num;
		return weight > oth.weight;
	}
};
void mymap::Prim() {
	int size = _m.size();
	priority_queue<edg> q;
	int curNode = 1;
	v[1].state = visited;
	while (--size > 1) {
		for (auto& p : _m[curNode])
			if (v[p.second].state != visited) {
				q.push(edg(p.first,p.second,curNode));
			}
		v[curNode].state = visited;		
		while (v[q.top().num].state == visited) q.pop();
		curNode = q.top().num;
		v[curNode].p = q.top().p;
	}
	for (int i = 1; i < v.size();++i) {
		cout << "(" << i << " " << v[i].p << ")" << "  ";
		cout << endl;
	}
}


int find(vector<int>& father,int val) {
	if (father[val] == val) return val;
	father[val] = find(father,father[val]);
	return father[val];
}
bool merge(vector<int>& father, int x, int y) {
	int a = find(father, x);
	int b = find(father, y);
	if (a == b) return true;
	father[a] = b;
	return false;
}
void mymap::Kruskal() {
	int size = _m.size();
	vector<int> father(size);
	priority_queue<edg> q;
	for (int i = 1; i < size; ++i) {
		father[i] = i;
		for (auto& p : _m[i]) {
			if(p.second>i)
				q.push(edg(p.first, p.second, i));
		}
	}
	while (size > 1) {
		while (merge(father, q.top().num, q.top().p)) q.pop();
		int num = q.top().num;
		int p = q.top().p;
		if (v[num].state != visited) {
			v[num].state = visited;
			--size;
		}
		if (v[p].state != visited) {
			v[p].state = visited;
			--size;
		}
		cout << num << " " << p << endl;
	}
}


void mymap::printPath(int curNode,int& start) {
	if (curNode == start) {
		cout << curNode << " ";
		return;
	}
	printPath(v[curNode].p, start);
	cout << curNode << " ";
}
void mymap::oriDijstra(int start,int end) {
	int curNode = start;
	v[curNode].state = visited;
	v[start].minpath = 0;
	while (curNode != end&&curNode!=0) {
		for (auto& p : _m[curNode]) {
			if (v[p.second].state != visited&&v[p.second].minpath > p.first + v[curNode].minpath) {
				v[p.second].minpath = p.first + v[curNode].minpath;
				v[p.second].p = curNode;
			}
		}		
		curNode = 0;
		for (int i = 1; i < v.size(); ++i) {
			if (v[i].state != visited&&v[i].minpath < v[curNode].minpath)
				curNode = i;
		}
		v[curNode].state = visited;
	}
	if (curNode == 0) {
		cout << "这两点之间没有路径" << endl;
		return;
	}
	cout << " 最短路径长度为：" << v[end].minpath << endl;
	cout << "路径是：" << endl;
	printPath(curNode, start);
}
void mymap::newDijstra(int start, int end) {
	mypriority_queue myq(_m.size());
	int curNode = start;
	v[curNode].state = visited;
	v[start].minpath = 0;
	while (curNode != end) {
		for (auto& p : _m[curNode]) {
			if (v[p.second].state != visited&&v[p.second].minpath > p.first + v[curNode].minpath) {
				v[p.second].minpath = p.first + v[curNode].minpath;
				v[p.second].p = curNode;
				if (v[p.second].state == ori) {
					myq.push({ v[p.second].minpath,p.second });
					v[p.second].state = inqueue;
				}
				else
					myq.change(p.second, v[p.second].minpath);				
			}
		}
		if (myq.empty()) break;
		curNode = myq.top().second;
		myq.pop();
		v[curNode].state = visited;
	}
	if (v[end].minpath==INT_MAX) {
		cout << "这两点之间没有路径" << endl;
		return;
	}
	cout << " 最短路径长度为：" << v[end].minpath << endl;
	cout << "路径是：" << endl;
	printPath(curNode, start);
}
*/