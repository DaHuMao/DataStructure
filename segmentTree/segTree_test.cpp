#include<iostream>
#include"segTree.hpp"

using namespace std;
int main(){
  vector<vector<int>> v2={{1,2,3},{12,7,98}};
  vector<int> v1={4,14,12,5,78,22};
  segTree<int, int> sg1(v1);
  segTree<vector<int>, int> sg2(v2);

  cout<<sg2.sum(vector<int>{0,0},vector<int>{1,2})<<endl;
  sg2.update(vector<int>{1,2},1);
  cout<<sg2.sum(vector<int>{0,0},vector<int>{1,2})<<endl;
  
  
  cout<<sg1.sum(vector<int>{0},vector<int>{3})<<endl;
  sg1.update(vector<int>{2},1);
  cout<<sg1.sum(vector<int>{0},vector<int>{3})<<endl;
return 0;
}
