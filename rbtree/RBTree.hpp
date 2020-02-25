#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<iterator>
#include<algorithm>


enum color
{
	red,
	black
};
template<class T>
struct RB_TreeNode 
{
	RB_TreeNode * left;
	RB_TreeNode * right;
	RB_TreeNode * p;
	T key;
	color color;
	RB_TreeNode (T x,RB_TreeNode<T>* _Guard) :key(x), left(_Guard), right(_Guard), p(_Guard), color(red) {};
	RB_TreeNode () : left(NULL), right(NULL), p(NULL), color(black) {};
	RB_TreeNode(T val) :key(val),left(NULL), right(NULL), p(NULL), color(black) {};
	void operator=(RB_TreeNode<T>& oth) {
		left = oth.left;
		color = oth.color;
		right = oth.right;
		key = oth.key;
		p = oth.p;
	}

	//寻找前驱
	RB_TreeNode<T>* findFront(RB_TreeNode<T>* _Guard)
	{
		RB_TreeNode<T>* t = this;
		if (t == _Guard) return t;
		if (t->left != _Guard)
		{
			 t = t->left;
			while (t->right != _Guard)
				t = t->right;
			return t;
		}
		else
		{
			while (t->p != _Guard&&t == t->p->left)
				t = t->p;
			return t->p;
		}
	}

	//寻找后继
	RB_TreeNode<T>* findSucceed(RB_TreeNode<T>* _Guard)
	{
		RB_TreeNode<T>* t = this;
		if (t == _Guard) return t;
		if (t->right != _Guard)
		{
			t = t->right;
			while (t->left != _Guard)
				t = t->left;
			return t;
		}
		else
		{
			while (t->p != _Guard&&t == t->p->right)
				t = t->p;
			return t->p;
		}
	}
};
template<class T>
struct Guard {
	RB_TreeNode<T> * left;
	RB_TreeNode<T> * right;
	RB_TreeNode<T> * p;
	Guard() :left(NULL), right(NULL), p(NULL) {};
};
// :public iterator<bidirectional_iterator_tag, value>
template<class value,class ref,class ptr>
struct rbtree_iterator {
	typedef rbtree_iterator<value, value&, value*> iterator;
	typedef RB_TreeNode<value>* link_type;
	typedef rbtree_iterator<value, ref, ptr> self;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef value value_type;
	typedef ptr pointer;
	typedef ref reference;
	typedef ptrdiff_t difference_type;
	link_type node;
	link_type _Guard;

	rbtree_iterator() {};
	rbtree_iterator(const link_type& x,const link_type& g):node(x),_Guard(g) {};
	rbtree_iterator(const iterator& it) :node(it.node), _Guard(it._Guard) {};
	
	
	self& operator=(const self& oth) { node = oth.node; return *this; };
	ref operator*() const { if (node == _Guard) { std::cout << "尝试访问边界迭代器" << std::endl; throw; } return node->key; };
	ptr operator->() const { if (node == _Guard) { std::cout << "尝试访问边界迭代器" << std::endl; throw; }return &(node->key); };
	self& operator++() { if (node == _Guard) { std::cout << "迭代器向后越界" << std::endl; throw; } node = node->findSucceed(_Guard); return *this; };
	self operator++(int) { if (node == _Guard) { std::cout << "迭代器向后越界" << std::endl; throw; } self tmp = *this; node = node->findSucceed(_Guard); return tmp; };
	self& operator--() { if (node == _Guard) { std::cout << "迭代器向前越界" << std::endl; throw; } node = node->findFront(_Guard); return *this; };
	self operator--(int) { if (node == _Guard) { std::cout << "迭代器向前越界" << std::endl; throw; }  self tmp = *this; node = node->findFront(_Guard); return tmp; };
	bool operator==(const self& oth) { return node == oth.node; };
	bool operator!=(const self& oth) { return !(node == oth.node); };

};


template<typename T>
class mycom {
public:
	bool operator() (const T& left, const T& right) {
		return left < right;
	}
};
template<class T, class keycompare = mycom<T>>
class RBTree {
public:
	typedef rbtree_iterator<T, T&, T*> iterator;
	typedef rbtree_iterator<T, const T&, const T*> const_iterator;

	RBTree(const keycompare& comp = keycompare());//默认构造函数
	RBTree(const RBTree<T,keycompare>& oth);
	RBTree(RBTree<T,keycompare>&& oth);//移动构造函数
    template<class _itr>
	RBTree(_itr begin, _itr end);//如果传入的是迭代器
	
	
	virtual~RBTree();

	///操作符重载
	RBTree<T,keycompare>& operator=(const RBTree<T, keycompare>& oth);
	RBTree<T,keycompare>& operator=(RBTree<T, keycompare>&& oth);
	const_iterator operator[](int i);

    


	void clear();//清空树
	int size();//返回树的数量
	bool empty();//判空
	int count(T val);//与val相等的元素的数量
	
	void insert(T value);//插入元素，可重复
	void insert_unique(T value);//插入元素，如果重复，后来的会代替现在的。
	

	//想怎么删除，就怎么删除
	void erase_unique(T value);//删除一个等于value的元素
	void erase_equal(T value); //删除所有等于value的元素
	void erase(const_iterator&& l, const_iterator&& r);//删除迭代器区间的元素
	void erase(const_iterator&& start, int n);//删除从指定迭代器开始的n个元素
	void erase(const_iterator&& it);//删除迭代器指向的元素

	////你要的迭代器  我都有	
	const_iterator begin();//返回最小元素的迭代器
	const_iterator end();  //返回一个边界，跟STL其他容器的end()差不多
	const_iterator back(); //返回最大元素的迭代器
	const_iterator start(); //返回一个边界，只不过是前边界，实际与end()地址相同，为了区别写了这么个函数
	const_iterator find(T val);//寻找指定元素第一次出现，返回一个迭代器；
	const_iterator findlast(T val);//寻找指定元素最后一次出现，返回一个迭代器；

	const_iterator lower_bound(T val);//如果元素存在，返回它第一次出现时的迭代器，若不存在返回它下边界迭代器
	const_iterator upper_bound(T val);//元素存在，返回最后一次出现迭代器，不存在，返回上边界迭代器

    //测试用的函数
	void pre_traverse();
	void mid_traverse(T* pt = NULL);
	void post_traverse();
	void print();
	RB_TreeNode<T>* guard();
	RB_TreeNode<T> * getroot();


private:
	void RBerase(RB_TreeNode<T>* node);//删除函数
	RB_TreeNode<T>*  RBTree_serch(T value, RB_TreeNode<T>* beginRoot);//寻找函数
	void RBTree_insert(T value, bool isunique);//插入函数
	void Left_Rotate(RB_TreeNode<T> * t);//左旋
	void Right_Rotate(RB_TreeNode<T> * t);//右旋
	void RBDELETE_Fixup(RB_TreeNode<T> * t);//删除后调整红黑特性
	void RBINSERT_Fixup(RB_TreeNode<T> * t);//插入后调整红黑特性
	RB_TreeNode<T>* findFront(RB_TreeNode<T>* t);//寻找前驱
	RB_TreeNode<T>* findSucceed(RB_TreeNode<T> * t);//寻找后继
	const_iterator findFandB(RB_TreeNode<T>* target, bool isForward);//寻找与指定值相等的最前面元素与最后面元素

	RB_TreeNode<T> * copyTree(const RB_TreeNode<T>* oth, RB_TreeNode<T>* p,  RB_TreeNode<T>*const& Guard);//拷贝
	void distroy(RB_TreeNode<T>* root);//销毁
	int findindex(RB_TreeNode<T>* root, int num, RB_TreeNode<T>*& tar, int& index);
	void relationGuard();
	
	void printNode(RB_TreeNode<T> * outT);
	RB_TreeNode<T>* _guard;
	RB_TreeNode<T>* _root;
	int _len;
	keycompare com;
	friend std::ostream& operator<<(std::ostream &out, RB_TreeNode<T> * outT);
};
  
     ////析构函数与构造函数
    template<class T,class keycompare>	
    RBTree<T,keycompare>::RBTree(const keycompare& comp):_len(0),com(comp), _guard(new RB_TreeNode<T>())
		 {
		_guard->left = _guard; 
		_guard->right = _guard;
		_root = _guard;
	}

	template<class T, class keycompare>
	RBTree<T, keycompare>::RBTree(const RBTree<T,keycompare>& oth):_guard(new RB_TreeNode<T>()),_len(oth._len){
		_root = copyTree(oth._root, _guard,oth._guard);
		relationGuard();
	}
	//移动构造函数
	template<class T, class keycompare>
	RBTree<T, keycompare>::RBTree(RBTree<T, keycompare>&& oth):_len(oth._len), _guard(oth._guard), _root(oth._root) {
		oth._root = NULL;
		oth._guard = NULL;
	}

	template<class T, class keycompare>
	template<class _itr>
	RBTree<T, keycompare>::RBTree(_itr begin,_itr end):_len(0), com(keycompare()), _guard(new RB_TreeNode<T>()), _root(_guard) {
		while (begin != end)
			insert(*(begin++));
	}

	template<class T, class keycompare>
	RBTree<T, keycompare>::~RBTree()
	{
		clear();
	}


	////操作符重载
	template<class T, class keycompare>
	RBTree<T, keycompare>& RBTree<T, keycompare>::operator=(const RBTree<T, keycompare>& oth) {
		clear();//在拷贝之前，先要释放已有资源
		_root = copyTree(oth._root, _guard);
		return *this;
	}

	//当参数为右值引用
	template<class T, class keycompare>
	RBTree<T, keycompare>& RBTree<T, keycompare>::operator=(RBTree<T, keycompare>&& oth) {
		clear();//在指向传进来的节点之前，要先释放原来的资源；
		_root = oth.root;
		return *this;
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::operator[] (int i) {
		if (i<0||i >= _len) {
      std::cout << "访问越界" << std::endl;
			throw;
		}
		RB_TreeNode<T>* tar = NULL;
		findindex(_root, 0, tar, ++i);
		return const_iterator(tar, _guard);
	}


	//判空，size,清除
	template<class T, class keycompare>
	void RBTree<T, keycompare>::clear() {
		if (_root == NULL)
		{
			_len = 0;
			return;
		}
		distroy(_root);
		_root = NULL;
		_len = 0;
	}

	template<class T, class keycompare>
	int RBTree<T, keycompare>::size()
	{
		return _len;
	}

	template<class T, class keycompare>
	bool  RBTree<T, keycompare>::empty() {
		return _len == 0;
	}

	template<class T, class keycompare>
	int RBTree<T, keycompare>::count(T val) {
		RB_TreeNode<T>* pval = RBTree_serch(val,_root);
		if (pval == _guard) return 0;
		int num=1;
		RB_TreeNode<T>* temp = pval->findFront(_guard);
		while (temp!=_guard&&!com(temp->key, val) && !com(val, temp->key)) {
			temp = temp->findFront(_guard);
			++num;
		}
		temp = pval->findSucceed(_guard);
		while (temp != _guard && !com(temp->key, val) && !com(val, temp->key)) {
			temp = temp->findSucceed(_guard);
			++num;
		}
		return num;
	}


	////各种插入与删除操作
	template<class T, class keycompare>
	void RBTree<T, keycompare>::insert(T value)
	{
		RBTree_insert(value, false);
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::insert_unique(T value) {
		RBTree_insert(value, true);
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::erase_unique(T value) {
		RBerase(RBTree_serch(value, _root));
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::erase_equal(T value) {
		RB_TreeNode<T>* tar = RBTree_serch(value, _root);
		if (tar == _guard) return;
		erase(findFandB(tar, true), ++findFandB(tar, false));
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::erase(const_iterator&& l, const_iterator&& r) {
		while (l != r&&l != end())
			erase(l++);
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::erase(const_iterator&& start, int n) {
		while (n--&&start != end()) erase(start++);
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::erase(const_iterator&& it) {
		RBerase(it.node);
	}


	///必要的迭代器
	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::begin() {
		return const_iterator(_guard->left, _guard);
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::end() {
		return const_iterator(_guard, _guard);
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::back() {
		return const_iterator(_guard->right, _guard);
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::start() {
		return end();
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::find(T val) {
		RB_TreeNode<T>* p = RBTree_serch(val, _root);
		if (p == _guard) return end();
		return findFandB(p, true);
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::findlast(T val) {
		RB_TreeNode<T>* p = RBTree_serch(val, _root);
		if (p == _guard) return end();
		return findFandB(p, false);
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::lower_bound(T val) {
		if (_len == 0) return end();
		RB_TreeNode<T>* root = _root;
		RB_TreeNode<T>* tmp = _guard;
		while (root != _guard) {
			tmp = root;
			if (com(val, root->key))
				root = root->left;
			else if (com(root->key, val))
				root = root->right;
			else {
				tmp = root;
				break;
			}
		}
		if (root == _guard) {
			if (!com(tmp->key, val))
				return const_iterator(findSucceed(tmp), _guard);
			else
				return const_iterator(tmp, _guard);
		}
		/*if (root == _guard) {
		if (com(val, tmp->key))
		return const_iterator(findFront(tmp), _guard);
		else
		return const_iterator(tmp, _guard);
		}*/
		return findFandB(tmp, true);
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::upper_bound(T val) {
		RB_TreeNode<T>* root = _root;
		RB_TreeNode<T>* tmp = _guard;
		while (root != _guard) {
			tmp = root;
			if (com(val, root->key))
				root = root->left;
			else if (com(root->key, val))
				root = root->right;
			else {
				tmp = root;
				break;
			}
		}
		if (root == _guard) {
			if (com(tmp->key, val))
				return const_iterator(findSucceed(tmp), _guard);
			else
				return const_iterator(tmp, _guard);
		}
		return findFandB(tmp, false);
	}




	////后面都是为了实现前面的接口的内部函数

	template<class T, class keycompare>
	RB_TreeNode<T>* RBTree<T, keycompare>::guard() {
		return _guard;
	}

	template<class T, class keycompare>
	RB_TreeNode<T> * RBTree<T, keycompare>::getroot()
	{
		return _root;
	}

    ///插入节点后调整红黑树满足红黑树五个特性

	//////左旋
	template<class T, class keycompare>
	void RBTree<T, keycompare>::Left_Rotate(RB_TreeNode<T> * t)
	{
		if (t == _guard || t->right == _guard)
		{
      std::cout << "左旋节点或节点右孩子不应为空" << std::endl;
			return;
		}
		RB_TreeNode<T> * tmp = t->right;
		tmp->p = t->p;
		if (t->p == _guard)
		{
			_root = tmp;
		}
		else if (t == t->p->left)
			t->p->left = tmp;
		else
			t->p->right = tmp;
		t->p = tmp;
		t->right = tmp->left;
		if (tmp->left != _guard)
			tmp->left->p = t;
		tmp->left = t;
	}

	////右旋
	template<class T, class keycompare>
	void RBTree<T, keycompare>::Right_Rotate(RB_TreeNode<T> * t)
	{
		if (!t || !t->left)
		{
      std::cout << "右旋节点或节点左孩子不应为空" << std::endl;
			return;
		}
		RB_TreeNode<T> * tmp = t->left;
		tmp->p = t->p;
		if (t->p == _guard)
		{
			_root = tmp;
		}
		else if (t == t->p->left)
			t->p->left = tmp;
		else
			t->p->right = tmp;
		t->p = tmp;
		t->left = tmp->right;
		if (tmp->right != _guard)
			tmp->right->p = t;
		tmp->right = t;
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::RBTree_insert(T value, bool isunique) {
		RB_TreeNode<T> * Tnode = new RB_TreeNode<T>(value, _guard);
		RB_TreeNode<T> * tmp = _root;
		RB_TreeNode<T> * Ptmp = _guard;
		if (_root == _guard)//如果插入的节点是第一个节点，相当于初始化根节点
		{
			_root = Tnode;
			_root->color = black;
			_len++;
			_guard->left = _root;
			_guard->right = _root;
			return;
		}

		//如果插入的节点小于最小值，直接插在最左边，并更新最小值节点
		if (com(value, _guard->left->key)) {
			Tnode->p = _guard->left;
			_guard->left->left = Tnode;
			_guard->left = Tnode;
		}
		//如果插入的节点大于等于最大值，直接插在最右边，更新最大值节点
		else if (!com(value, _guard->right->key)) {
			if (!com(_guard->right->key, value) && isunique) {
        std::swap(_guard->right->key, tmp->key);
				delete Tnode;
				return;
			}
			Tnode->p = _guard->right;
			_guard->right->right = Tnode;
			_guard->right = Tnode;
		}
		else {

			///以上三种情况都不属于寻找合适的插入节点，就一直往下找，直到边界条件(找到了空节点，在我这是_guard)
			while (tmp != _guard)
			{
				Ptmp = tmp;
				if (com(value, tmp->key))
					tmp = tmp->left;
				else if (com(tmp->key, value))
					tmp = tmp->right;
				else {
					if (isunique) {
            std::swap(Tnode->key, tmp->key);
						delete Tnode;
						return;
					}
					tmp = tmp->right;
				}
			}
			///更新插入节点的父亲，以及该父亲的孩子须得指向它
			Tnode->p = Ptmp;
			if (com(Tnode->key, Ptmp->key))
				Ptmp->left = Tnode;
			else
				Ptmp->right = Tnode;
		}
		///如果插入节点的父亲是红色，则违反了红黑树红黑特性，需要调整
		if (Tnode->p->color == red)
			RBINSERT_Fixup(Tnode);
		_len++;///别忘了更新元素数目
	}

	/////删除节点
	template<class T, class keycompare>
	void RBTree<T, keycompare>::RBerase(RB_TreeNode<T>* node)
	{
		RB_TreeNode<T>* t = node;
		if (t == _guard) return;
		RB_TreeNode<T>* tmp;
		if (t->left != _guard&&t->right != _guard)
		{
			///节点左右孩子都不是边界节点，交换信息
			RB_TreeNode<T>* succ = findSucceed(t);
			if (t == t->p->left)
				t->p->left = succ;
			else
				t->p->right = succ;
			if (succ == succ->p->left)
				succ->p->left = t;
			else
				succ->p->right = t;
      std::swap(succ->p, t->p);
      std::swap(succ->color, t->color);
      std::swap(succ->left, t->left);
      std::swap(succ->right, t->right);
			succ->left->p = succ;
			succ->right->p = succ;
			if (t->left != _guard)
				t->left->p = t;
			if (t->right != _guard)
				t->right->p = t;
			if (succ->p == _guard) _root = succ;
			//这里其实最简单的方法是交换两个key然后直接删除succ，但是这样做会令原来指向succ的迭代器失效，所以要逐个交换。
		}
		///这里就是的tmp就是我们需要跟删除节点父亲建立联系的孩子节点
		if (t->left == _guard)
			tmp = t->right;
		else
			tmp = t->left;
		///如果删除的是最小值或者最大值，要更新_guard孩子
		if (t == _guard->left)
			_guard->left = findSucceed(t);
		if (t == _guard->right)
			_guard->right = findFront(t);
		if (t->p == _guard) _root = tmp;///如果是根，要及时更新根节点
		else if (t == t->p->left)///tmp 取代原来t的位置
			t->p->left = tmp;
		else
			t->p->right = tmp;
		tmp->p = t->p;
		if (t->color == black)///如果被删除的节点是黑色，需要调整红黑树红黑特性
		{
			RBDELETE_Fixup(tmp);
		}
		_len--;
		delete t;
		t = NULL;
		return;
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::RBINSERT_Fixup(RB_TreeNode<T> * t)
	{
		RB_TreeNode<T> * tmp = t->p;
		RB_TreeNode<T> * Pbra = _guard;
		//出递归的条件，就是节点是黑色
		while (tmp->color==red)
		{
			//这个就是我们讨论的当插入节点是左孩子的时候
			if (tmp == tmp->p->left)
			{
				Pbra = tmp->p->right;
				///第一种情况 叔叔是红色
				if (Pbra!=_guard&&Pbra->color == red)
				{
					tmp->color = black;
					tmp->p->color = red;
					Pbra->color = black;
					t = tmp->p;//当前节点变成祖父节点
					tmp = t->p;//同时更新父节点为祖父节点的父亲节点
				}
				else
				{
					///叔叔是黑色
					if (t == tmp->right)///插入节点是右孩子，左旋，变成第三种情况
					{
						Left_Rotate(tmp);
						tmp = t;//注意这里左旋之后，孩子父亲角色换了
					}
					tmp->color = black;//tmp颜色变黑，达到出循环的条件
					tmp->p->color = red;
					Right_Rotate(tmp->p);
				}							
			}
			else//这边是插入节点是右孩子的情况，与上面是对称的
			{
				Pbra = tmp->p->left;
				if (Pbra!=_guard&&Pbra->color == red)
				{
					tmp->color = black;
					tmp->p->color = red;
					Pbra->color = black;
					t = tmp->p;
					tmp = t->p;
				}
				else
				{
					if (t == tmp->left)
					{
						Right_Rotate(tmp);
						tmp = t;
					}
					tmp->color = black;
					tmp->p->color = red;
					Left_Rotate(tmp->p);
				}
			}
			if (tmp==_guard)//说明当前节点是根节点，因为只有根节点的父节点是边界节点_guard
			{
				///这里其实可以直接将t的颜色变成黑色，然后直接出循环
				tmp = t;
				tmp->color = black;
			}
		}		
	}

	///删除节点后调整红黑树满足红黑树五个特性
	template<class T, class keycompare>
	void RBTree<T, keycompare>::RBDELETE_Fixup(RB_TreeNode<T> * t)
	{
		RB_TreeNode<T> * w = NULL;
		while (t!=_root&&t->color==black)
		{
			////要连接的孩子节点是左孩子的情况
			if (t == t->p->left)
			{
				w = t->p->right;//兄弟节点
				////第一种情况
				if (w->color == red)///兄弟是红色
				{
					///交换兄弟与父亲的颜色，因为兄弟颜色是红色，父亲肯定是黑色，所以直接赋值
					t->p->color = red;
					w->color = black;
					Left_Rotate(t->p);
				}
				else
				{
					///兄弟右孩子是红色，就是第四种情况
					if (w->right->color == red)
					{
						w->color = t->p->color;
						t->p->color = black;
						w->right->color = black;
						Left_Rotate(t->p);
						t = _root;///这里是为了最后一句，出循环后要把t染成黑色，将t设置为根节点，可以出循环，将根节点染黑没影响
					}
					else if (w->left->color == red)///右孩子是黑色，左孩子红色
					{
						w->color = red;
						w->left->color = black;
						Right_Rotate(w);
						w = w->p;//别忘了右旋之后更新兄弟
					}
					else
					{
						///两个孩子都是黑色，也就是第二种情况，把兄弟染红，将另一重黑色往上推，也就是父亲节点
						w->color = red;
						t = t->p;
					}

				}
			}
			///这边是当前节点是右孩子的情况 完全对称
			else
			{
				w = t->p->left;
				if (w->color == red)
				{
					t->p->color = red;
					w->color = black;
					Right_Rotate(t->p);
				}
				else
				{
					if (w->left != _guard&&w->left->color == red)
					{
						w->color = t->p->color;
						t->p->color = black;
						w->left->color = black;
						Right_Rotate(t->p);
						t = _root;
					}
					else if (w->right != _guard&&w->right->color == red)
					{
						w->color = red;
						w->right->color = black;
						Left_Rotate(w);
						w = w->p;
					}
					else
					{
						w->color = red;
						t = t->p;
					}
				}
			}
		}
		t->color = black;///出循环要么是t是红色，要么t是根节点，直接染黑。
	}
	
    /////以beginRoot为根的子树开始寻找节点
	template<class T, class keycompare>
	RB_TreeNode<T>*  RBTree<T, keycompare>::RBTree_serch(T value, RB_TreeNode<T>* beginRoot)
	{
		RB_TreeNode<T> * p = beginRoot;
		while (p != _guard)
		{
			if (com(p->key, value))
				p = p->right;
			else if (com(value, p->key))
				p = p->left;
			else
				return p;
		}
		return p;
	}

	///////寻找前驱
	template<class T, class keycompare>
	RB_TreeNode<T>* RBTree<T, keycompare>::findFront(RB_TreeNode<T>* t)
	{
		return t->findFront(_guard);
	}

	/////寻找后继
	template<class T, class keycompare>
	RB_TreeNode<T>* RBTree<T, keycompare>::findSucceed(RB_TreeNode<T> * t)
	{
		return t->findSucceed(_guard);
	}


	template<class T, class keycompare>
	RB_TreeNode<T> * RBTree<T, keycompare>::copyTree(const RB_TreeNode<T>* oth, RB_TreeNode<T>* p, RB_TreeNode<T>* const& Guard) {
		if (oth == Guard) return _guard;
		RB_TreeNode<T>* root = new RB_TreeNode<T>(oth->key);
		root->color = oth->color;
		root->p = p;
		root->left = copyTree(oth->left, root, Guard);
		root->right = copyTree(oth->right, root, Guard);
		return root;
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::distroy(RB_TreeNode<T>* root) {
		if (root == _guard) return;
		distroy(root->left);
		distroy(root->right);
		delete root;
	}

	template<class T, class keycompare>
	int RBTree<T, keycompare>::findindex(RB_TreeNode<T>* root, int num, RB_TreeNode<T>*& tar, int& index) {
		if (tar != NULL || root == _guard) return 0;
		int l = findindex(root->left, 0, tar, index);
		if (l + 1 + num == index) {
			tar = root;
			return 0;
		}
		int r = findindex(root->right, l + 1+num, tar, index);
		return l + r + 1;
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*>  RBTree<T, keycompare>::findFandB(RB_TreeNode<T>* target, bool isForward) {
		if (isForward) {
			RB_TreeNode<T>* succ = findFront(target);
			while (succ != _guard && !com(target->key, succ->key) && !com(succ->key, target->key)) {
				target = succ;
				succ = findFront(succ);
			}
			return const_iterator(target, _guard);
		}
		else {
			RB_TreeNode<T>* succ = findSucceed(target);
			while (succ != _guard && !com(target->key, succ->key) && !com(succ->key, target->key)) {
				target = succ;
				succ = findSucceed(succ);
			}
			return const_iterator(target, _guard);
		}
		return const_iterator(_guard, _guard);
	}


	template<class T, class keycompare>
	void  RBTree<T, keycompare>::relationGuard() {
		RB_TreeNode<T>* node = _root;
		while (node->left != _guard)
			node = node->left;
		_guard->left = node;
		node = _root;
		while (node->right != _guard)
			node = node->right;
		_guard->right = node;
	}



	////自己测试用的函数
	/////前序遍历
	template<class T, class keycompare>
	void RBTree<T, keycompare>::pre_traverse()
	{

	}

	////中序遍历
	template<class T, class keycompare>
	void RBTree<T, keycompare>::mid_traverse(T* pt)
	{
		RB_TreeNode<T> * p = _root;
    std::stack<RB_TreeNode<T> *> s;
		while (true)
		{
			while (p!=_guard)
			{
				s.push(p);
				p = p->left;
			}

			if (s.empty()) break;
			p = s.top();
			if (pt == NULL)
				std::cout << p->key << " ";
			else
				*(pt++) = p->key;
			s.pop();
			p = p->right;
		}
    std::cout << std::endl;
	}

	/////后序遍历
	template<class T, class keycompare>
	void RBTree<T, keycompare>::post_traverse() {

	}

	/////层次遍历
	template<class T, class keycompare>
	void RBTree<T, keycompare>::print() {
		RB_TreeNode<T> * pRoot = _root;
		if (!pRoot) return;
    std::vector<std::queue<RB_TreeNode<T> *> > vq(2);
		int index = 0;
		vq[index].push(pRoot);
		while (!vq[index].empty() || !vq[1 - index].empty())
		{
			while (!vq[index].empty())
			{
				RB_TreeNode<T> * p = vq[index].front();
				vq[index].pop();
				printNode(p);
				if (p->left != _guard)
					vq[1 - index].push(p->left);
				if (p->right != _guard)
					vq[1 - index].push(p->right);
			}
      std::cout << std::endl;
			index = 1 - index;
		}
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::printNode(RB_TreeNode<T> * outT) {
		if (outT == _guard) return ;
    std::cout << "[" << " " << "key:" << outT->key << " ";
		if (outT->color == 0)
			std::cout << "color:" << "red" << " ";
		else
			std::cout << "color:" << "black" << " ";
		if (outT->left != _guard)
			std::cout << "left:" << outT->left->key << " ";
		if (outT->right != _guard)
			std::cout << "right:" << outT->right->key << " ";
		if (outT->p != _guard)
			std::cout << "parent:" << outT->p->key << " ";
    std::cout << "]";
	}


template<typename T>
std::ostream& operator<<(std::ostream &out, RB_TreeNode<T> * outT)
{

	return out;
}

