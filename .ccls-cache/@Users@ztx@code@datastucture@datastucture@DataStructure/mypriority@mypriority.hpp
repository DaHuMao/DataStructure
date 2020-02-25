
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


/*
class mypriority_queue {
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
*/
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

