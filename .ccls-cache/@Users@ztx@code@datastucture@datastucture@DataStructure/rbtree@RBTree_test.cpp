#include"RBTree.hpp"
#include<iostream>
#include<fstream>
#include<set>
using namespace std;

clock_t start, finish;
void printTime(const char* s,clock_t t){
  cout<<s<<t/CLOCKS_PER_SEC<<"s "<<t%CLOCKS_PER_SEC<<"ms"<<endl;
}
void insert_erase_rbtree(int num){
  RBTree<int> s;
  for (int i = 0; i < num; i++) {
    int a = rand() % num;
    s.insert(a);
  }
  for (int i = 0; i < num; i++) {
    int a = rand() % num;
    s.erase_equal(a);
  }
}
void insert_erase_set(int num){
  multiset<int> s;
  for (int i = 0; i < num; i++) {
    int a = rand() % num;
    s.insert(a);
  }
  for (int i = 0; i < num; i++) {
    int a = rand() % num;
    s.erase(a);
  }
}
 
ifstream infile;
ofstream outfile;
const int MAXN = 500005;
 
int X[MAXN];
int S[MAXN];
long long sum[MAXN];
 
void erase_one(multiset<long long> &s, long long x) {
	auto it = s.find(x);
  if(it==s.end())
    cout<<"s.end1()"<<x<<endl;
  else
    s.erase(it++);
}
void erase_one(RBTree<long long> &s, long long x) {
	auto it = s.find(x);
  if(it==s.end())
    cout<<"s.end2()"<<x<<endl;
  else
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
		auto it = s.upper_bound(sum[i] - D);
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



void test_google(int isSet){
	int T;
	infile >> T;
	for (int i = 1; i <= T; i++) {
		outfile << "Case #" << i << ": ";
    if(isSet > 0)
      solve();
    else
      solve1();
	}
} 

void execute_func(const char* str,void (*fun)(int),int func_pram){
  start=clock();
  fun(func_pram);
  finish=clock() - start;
  start=clock();
  printTime(str, finish);
}

int main() {

  vector<int> v={8,2,9,1,16,8,4,3};
  RBTree<int> rb(v.begin(),v.end());
 
  cout<<"start  tarversal in rbtree with initialization of vector{8 ,2 ,9, 1, 16, 8, 4, 3}"<<endl;
  for(auto it=rb.begin();it!=rb.end();++it)
    cout<<*it<<" ";
  cout<<endl;

  auto it=rb.lower_bound(5);
  cout<<"lower_bound 5: "<<*(it)<<endl;
  it=rb.upper_bound(5);
  cout<<"upper_bound 5: "<<*(it)<<endl;
  cout<<endl;
  int num=10000000;

  cout<<"rbtree and set start insert and erase "<<num<<" data separately"<<endl;
  execute_func("set useing time: ", insert_erase_set, num);
  execute_func("RBTree useing time: ", insert_erase_rbtree, num);
  
  cout<<endl;
  cout<<"------google kickstart test-------"<<endl;
  infile.open("./A-large-practice.in");
	outfile.open("./A-large-practice.out");

  execute_func("set using time in a kickstart example: ", test_google, 1);

  infile.close();
  outfile.close();
	
  infile.open("./A-large-practice.in");
	outfile.open("./A-large-practice1.out");
  
  execute_func("RBTree using time in a kickstart example: ", test_google, 0);
  
  infile.close();
  outfile.close();
	return 0;
}
