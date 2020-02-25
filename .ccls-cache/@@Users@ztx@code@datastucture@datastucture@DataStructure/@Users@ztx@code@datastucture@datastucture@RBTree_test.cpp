#include"RBTree.hpp"
#include<iostream>
#include<fstream>
#include<set>
using namespace std;

clock_t start, finish;
void printTime(const string&& s,clock_t t){
  cout<<s<<t/CLOCKS_PER_SEC<<"s "<<t%CLOCKS_PER_SEC<<"ms"<<endl;
}
void test(int num) {
time_t rawtime;
time(&rawtime);
struct tm * ti = localtime(&rawtime);

int v[10000];

RBTree<int> t;
multiset<int> s;
//int time1 = ti->tm_min * 60 + ti->tm_sec;
start=clock();
cout << "=====RBtree开始插入"<<num<<"个数据=====:" << endl;

for (int i = 0; i < num; i++) {
	int a = rand() % INT_MAX;
	t.insert(a);
	//s.insert(a);
}
finish=clock() - start;
start=clock();
printTime("RBTree插入完成，用时： ",finish);
cout << "set开始插入"<<num<<"个数据====="<<endl;
for (int i = 0; i < num; i++) {
	int a = rand() % INT_MAX;
	s.insert(a);
}

finish=clock() - start;
start=clock();
printTime("set插入完成，用时： ",finish);
//t.mid_traverse();
auto it1 = t.begin();
auto it2 = s.begin();
cout << "===rbtree开始删除====="<<endl;
while (it1 != t.end()) {
	t.erase(it1++);
}
finish=clock() - start;
start=clock();
if (it1 == t.end()) {
  printTime("RBTree 删除完成，用时： ", finish);
}
cout << "===set开始删除======"<<endl;
while (it2 != s.end()) {
	s.erase(it2++);
}
finish=clock() - start;
start=clock();
if (it2 == s.end()) {
  printTime("set 删除完成，用时： ", finish);
}
int cnt = 0;
}

 
ifstream infile;
ofstream outfile;
const int MAXN = 500005;
 
int X[MAXN];
int S[MAXN];
long long sum[MAXN];
 
void erase_one(multiset<long long> &s, long long x) {
	auto it = s.find(x);
	auto it1 = it;
	it1++;
	s.erase(it++);
}
 
void solve() {
	int N, O;
	long long D;
	infile >> N >> O >> D;
	int X1, X2, A, B, C, M, L;
	infile >> X1 >> X2 >> A >> B >> C >> M >> L;
	X[1] = X1, X[2] = X2;
	for (int i = 3; i <= N; i++) {
		X[i] = (1LL * A * X[i - 1] + 1LL * B * X[i - 2] + C) % M;
	}
	for (int i = 1; i <= N; i++) {
		S[i] = X[i] + L;
		sum[i] = sum[i - 1] + S[i];
	}
	int cnt_odd = 0;
	int l = 1;
	multiset<long long> s;
	long long ans = -0x3f3f3f3f3f3f3f3fLL;
	for (int i = 1; i <= N; i++) {
		s.insert(sum[i - 1]);
		cnt_odd += S[i] & 1;
		while (cnt_odd > O) {
			erase_one(s, sum[l - 1]);
			//s.erase_unique(sum[l - 1]);
			cnt_odd -= S[l] & 1;
			l++;
		}
		auto it = s.lower_bound(sum[i] - D);
		if (it != s.end()) {
			ans = std::max(ans, sum[i] - *it);
		}
	}
	if (ans == -0x3f3f3f3f3f3f3f3fLL) {
		outfile << "IMPOSSIBLE" << endl;
	}
	else {
		outfile << ans << endl;
	}
}


void solve1() {
	int N, O;
	long long D;
	infile >> N >> O >> D;
	int X1, X2, A, B, C, M, L;
	infile >> X1 >> X2 >> A >> B >> C >> M >> L;
	X[1] = X1, X[2] = X2;
	for (int i = 3; i <= N; i++) {
		X[i] = (1LL * A * X[i - 1] + 1LL * B * X[i - 2] + C) % M;
	}
	for (int i = 1; i <= N; i++) {
		S[i] = X[i] + L;
		sum[i] = sum[i - 1] + S[i];
	}
	int cnt_odd = 0;
	int l = 1;
  RBTree<long long> s;
	long long ans = -0x3f3f3f3f3f3f3f3fLL;
	for (int i = 1; i <= N; i++) {
		s.insert(sum[i - 1]);
		cnt_odd += S[i] & 1;
		while (cnt_odd > O) {
			//erase_one(s, sum[l - 1]);
			s.erase_unique(sum[l - 1]);
			cnt_odd -= S[l] & 1;
			l++;
		}
		auto it = s.lower_bound(sum[i] - D);
		if (it != s.end()) {
			ans = std::max(ans, sum[i] - *it);
		}
	}
	if (ans == -0x3f3f3f3f3f3f3f3fLL) {
		outfile << "IMPOSSIBLE" << endl;
	}
	else {
		outfile << ans << endl;
	}
}



void test_google(bool isSet){
	int T;
	infile >> T;
	for (int i = 1; i <= T; i++) {
		outfile << "Case #" << i << ": ";
    if(isSet)
      solve();
    else
      solve1();
	}
} 
int main() {
  cout<<"插入数据，删除数据"<<endl;
  test(5000000);
  cout<<endl;

  cout<<"------google kickstart test-------"<<endl;
  infile.open("./A-large-practice.in");
	outfile.open("./A-large-practice.out");
  
  start=clock();
  test_google(false);
  finish=clock() - start;
  start=clock();
  printTime("RBTree in google test: using time: ", finish);

  infile.close();
  outfile.close();
	
  infile.open("./A-large-practice.in");
	outfile.open("./A-large-practice1.out");
  
  start=clock();
  test_google(true);
  finish=clock() - start;
  start=clock();
  printTime("set in google test: using time: ", finish);
  
  infile.close();
  outfile.close();
	return 0;
}
