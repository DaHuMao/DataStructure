#include<iostream>
template<class T>
class A{};

template<class T,class kk>
class B{
  public:
    B(T a,kk b);
    B();
};

template<class T,class kk>
B<T,kk>::B(T a,kk b){
  std::cout<<"t kk"<<std::endl;
}
template<class T,class kk>
B<T,kk>::B(){
  std::cout<<"default"<<std::endl;
}
int fun(int a,int b=10);
#define TAG "ztxztx"
int main(){
  std::cout<<TAG<<std::endl;
  std::cout<<fun(1)<<std::endl;
  std::cout<<TAG<<std::endl;
  B<int,int> b;
  std::cout<<"hello world"<<std::endl;
  return 0;
}
int fun(int a,int b){
#undef TAG
#define TAG "txytxy"
  std::cout<<TAG<<std::endl;
  return a+b;
}
