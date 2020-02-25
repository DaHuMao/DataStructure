#pragma once
#include"heap_tree.h"
template<class T>
struct heap_tree {
	T val;
	heap_tree<T>* parent;
	heap_tree<T>* left;
	heap_tree<T>* right;
	heap_tree(T x = 0) :val(x), left(NULL), right(NULL), parent(NULL) {}
};

//template<typename T>
//using ht<T>= heap_tree<T> ht<T> ;

/*template<class T>
class left_heap {
	left_heap() {}
	left_heap(left_heap& oth) {}
	left_heap(left_heap&& oth) {}
	left_heap& operator=(left_heap& oth) {}
	left_heap& oprator = (left_heap&& oth){}
	left_heap& merge(const left_heap& a, const left_heap& b) {}
	T top() { return root->val; }
private:
	int size;
	ht<T> root;
};*/
