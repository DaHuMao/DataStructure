#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<iterator>
#include<algorithm>
using namespace std;


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

	//Ѱ��ǰ��
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

	//Ѱ�Һ��
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
	typedef bidirectional_iterator_tag iterator_category;
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
	ref operator*() const { if (node == _Guard) { cout << "���Է��ʱ߽������" << endl; throw; } return node->key; };
	ptr operator->() const { if (node == _Guard) { cout << "���Է��ʱ߽������" << endl; throw; }return &(node->key); };
	self& operator++() { if (node == _Guard) { cout << "���������Խ��" << endl; throw; } node = node->findSucceed(_Guard); return *this; };
	self operator++(int) { if (node == _Guard) { cout << "���������Խ��" << endl; throw; } self tmp = *this; node = node->findSucceed(_Guard); return tmp; };
	self& operator--() { if (node == _Guard) { cout << "��������ǰԽ��" << endl; throw; } node = node->findFront(_Guard); return *this; };
	self operator--(int) { if (node == _Guard) { cout << "��������ǰԽ��" << endl; throw; }  self tmp = *this; node = node->findFront(_Guard); return tmp; };
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

	RBTree(const keycompare& comp = keycompare());//Ĭ�Ϲ��캯��
	RBTree(const RBTree<T,keycompare>& oth);
	RBTree(RBTree<T,keycompare>&& oth);//�ƶ����캯��
    template<class _itr>
	RBTree(_itr begin, _itr end);//���������ǵ�����
	
	
	virtual~RBTree();

	///����������
	RBTree<T,keycompare>& operator=(const RBTree<T, keycompare>& oth);
	RBTree<T,keycompare>& operator=(RBTree<T, keycompare>&& oth);
	const_iterator operator[](int i);

    


	void clear();//�����
	int size();//������������
	bool empty();//�п�
	int count(T val);//��val��ȵ�Ԫ�ص�����
	
	void insert(T value);//����Ԫ�أ����ظ�
	void insert_unique(T value);//����Ԫ�أ�����ظ��������Ļ�������ڵġ�
	

	//����ôɾ��������ôɾ��
	void erase_unique(T value);//ɾ��һ������value��Ԫ��
	void erase_equal(T value); //ɾ�����е���value��Ԫ��
	void erase(const_iterator&& l, const_iterator&& r);//ɾ�������������Ԫ��
	void erase(const_iterator&& start, int n);//ɾ����ָ����������ʼ��n��Ԫ��
	void erase(const_iterator&& it);//ɾ��������ָ���Ԫ��

	////��Ҫ�ĵ�����  �Ҷ���	
	const_iterator begin();//������СԪ�صĵ�����
	const_iterator end();  //����һ���߽磬��STL����������end()���
	const_iterator back(); //�������Ԫ�صĵ�����
	const_iterator start(); //����һ���߽磬ֻ������ǰ�߽磬ʵ����end()��ַ��ͬ��Ϊ������д����ô������
	const_iterator find(T val);//Ѱ��ָ��Ԫ�ص�һ�γ��֣�����һ����������
	const_iterator findlast(T val);//Ѱ��ָ��Ԫ�����һ�γ��֣�����һ����������

	const_iterator lower_bound(T val);//���Ԫ�ش��ڣ���������һ�γ���ʱ�ĵ��������������ڷ������±߽������
	const_iterator upper_bound(T val);//Ԫ�ش��ڣ��������һ�γ��ֵ������������ڣ������ϱ߽������

    //�����õĺ���
	void pre_traverse();
	void mid_traverse(T* pt = NULL);
	void post_traverse();
	void print();
	RB_TreeNode<T>* guard();
	RB_TreeNode<T> * getroot();


private:
	void RBerase(RB_TreeNode<T>* node);//ɾ������
	RB_TreeNode<T>*  RBTree_serch(T value, RB_TreeNode<T>* beginRoot);//Ѱ�Һ���
	void RBTree_insert(T value, bool isunique);//���뺯��
	void Left_Rotate(RB_TreeNode<T> * t);//����
	void Right_Rotate(RB_TreeNode<T> * t);//����
	void RBDELETE_Fixup(RB_TreeNode<T> * t);//ɾ��������������
	void RBINSERT_Fixup(RB_TreeNode<T> * t);//���������������
	RB_TreeNode<T>* findFront(RB_TreeNode<T>* t);//Ѱ��ǰ��
	RB_TreeNode<T>* findSucceed(RB_TreeNode<T> * t);//Ѱ�Һ��
	const_iterator findFandB(RB_TreeNode<T>* target, bool isForward);//Ѱ����ָ��ֵ��ȵ���ǰ��Ԫ���������Ԫ��

	RB_TreeNode<T> * copyTree(const RB_TreeNode<T>* oth, RB_TreeNode<T>* p,  RB_TreeNode<T>*const& Guard);//����
	void distroy(RB_TreeNode<T>* root);//����
	int findindex(RB_TreeNode<T>* root, int num, RB_TreeNode<T>*& tar, int& index);
	void relationGuard();
	
	void printNode(RB_TreeNode<T> * outT);
	RB_TreeNode<T>* _guard;
	RB_TreeNode<T>* _root;
	int _len;
	keycompare com;
	friend ostream& operator<<(ostream &out, RB_TreeNode<T> * outT);
};
  
     ////���������빹�캯��
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
	//�ƶ����캯��
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


	////����������
	template<class T, class keycompare>
	RBTree<T, keycompare>& RBTree<T, keycompare>::operator=(const RBTree<T, keycompare>& oth) {
		clear();//�ڿ���֮ǰ����Ҫ�ͷ�������Դ
		_root = copyTree(oth._root, _guard);
		return *this;
	}

	//������Ϊ��ֵ����
	template<class T, class keycompare>
	RBTree<T, keycompare>& RBTree<T, keycompare>::operator=(RBTree<T, keycompare>&& oth) {
		clear();//��ָ�򴫽����Ľڵ�֮ǰ��Ҫ���ͷ�ԭ������Դ��
		_root = oth.root;
		return *this;
	}

	template<class T, class keycompare>
	rbtree_iterator<T, const T&, const T*> RBTree<T, keycompare>::operator[] (int i) {
		if (i<0||i >= _len) {
			cout << "����Խ��" << endl;
			throw;
		}
		RB_TreeNode<T>* tar = NULL;
		findindex(_root, 0, tar, ++i);
		return const_iterator(tar, _guard);
	}


	//�пգ�size,���
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


	////���ֲ�����ɾ������
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


	///��Ҫ�ĵ�����
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
		RB_TreeNode<T>* tmp = NULL;
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
		RB_TreeNode<T>* tmp = NULL;
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




	////���涼��Ϊ��ʵ��ǰ��Ľӿڵ��ڲ�����

	template<class T, class keycompare>
	RB_TreeNode<T>* RBTree<T, keycompare>::guard() {
		return _guard;
	}

	template<class T, class keycompare>
	RB_TreeNode<T> * RBTree<T, keycompare>::getroot()
	{
		return _root;
	}

    ///����ڵ�������������������������

	//////����
	template<class T, class keycompare>
	void RBTree<T, keycompare>::Left_Rotate(RB_TreeNode<T> * t)
	{
		if (t == _guard || t->right == _guard)
		{
			cout << "�����ڵ��ڵ��Һ��Ӳ�ӦΪ��" << endl;
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

	////����
	template<class T, class keycompare>
	void RBTree<T, keycompare>::Right_Rotate(RB_TreeNode<T> * t)
	{
		if (!t || !t->left)
		{
			cout << "�����ڵ��ڵ����Ӳ�ӦΪ��" << endl;
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
		if (_root == _guard)//�������Ľڵ��ǵ�һ���ڵ㣬�൱�ڳ�ʼ�����ڵ�
		{
			_root = Tnode;
			_root->color = black;
			_len++;
			_guard->left = _root;
			_guard->right = _root;
			return;
		}

		//�������Ľڵ�С����Сֵ��ֱ�Ӳ�������ߣ���������Сֵ�ڵ�
		if (com(value, _guard->left->key)) {
			Tnode->p = _guard->left;
			_guard->left->left = Tnode;
			_guard->left = Tnode;
		}
		//�������Ľڵ���ڵ������ֵ��ֱ�Ӳ������ұߣ��������ֵ�ڵ�
		else if (!com(value, _guard->right->key)) {
			if (!com(_guard->right->key, value) && isunique) {
				swap(_guard->right->key, tmp->key);
				delete Tnode;
				return;
			}
			Tnode->p = _guard->right;
			_guard->right->right = Tnode;
			_guard->right = Tnode;
		}
		else {

			///�������������������Ѱ�Һ��ʵĲ���ڵ㣬��һֱ�����ң�ֱ���߽�����(�ҵ��˿սڵ㣬��������_guard)
			while (tmp != _guard)
			{
				Ptmp = tmp;
				if (com(value, tmp->key))
					tmp = tmp->left;
				else if (com(tmp->key, value))
					tmp = tmp->right;
				else {
					if (isunique) {
						swap(Tnode->key, tmp->key);
						delete Tnode;
						return;
					}
					tmp = tmp->right;
				}
			}
			///���²���ڵ�ĸ��ף��Լ��ø��׵ĺ������ָ����
			Tnode->p = Ptmp;
			if (com(Tnode->key, Ptmp->key))
				Ptmp->left = Tnode;
			else
				Ptmp->right = Tnode;
		}
		///�������ڵ�ĸ����Ǻ�ɫ����Υ���˺����������ԣ���Ҫ����
		if (Tnode->p->color == red)
			RBINSERT_Fixup(Tnode);
		_len++;///�����˸���Ԫ����Ŀ
	}

	/////ɾ���ڵ�
	template<class T, class keycompare>
	void RBTree<T, keycompare>::RBerase(RB_TreeNode<T>* node)
	{
		RB_TreeNode<T>* t = node;
		if (t == _guard) return;
		RB_TreeNode<T>* tmp;
		if (t->left != _guard&&t->right != _guard)
		{
			///�ڵ����Һ��Ӷ����Ǳ߽�ڵ㣬������Ϣ
			RB_TreeNode<T>* succ = findSucceed(t);
			if (t == t->p->left)
				t->p->left = succ;
			else
				t->p->right = succ;
			if (succ == succ->p->left)
				succ->p->left = t;
			else
				succ->p->right = t;
			swap(succ->p, t->p);
			swap(succ->color, t->color);
			swap(succ->left, t->left);
			swap(succ->right, t->right);
			succ->left->p = succ;
			succ->right->p = succ;
			if (t->left != _guard)
				t->left->p = t;
			if (t->right != _guard)
				t->right->p = t;
			if (succ->p == _guard) _root = succ;
			//������ʵ��򵥵ķ����ǽ�������keyȻ��ֱ��ɾ��succ����������������ԭ��ָ��succ�ĵ�����ʧЧ������Ҫ���������
		}
		///������ǵ�tmp����������Ҫ��ɾ���ڵ㸸�׽�����ϵ�ĺ��ӽڵ�
		if (t->left == _guard)
			tmp = t->right;
		else
			tmp = t->left;
		///���ɾ��������Сֵ�������ֵ��Ҫ����_guard����
		if (t == _guard->left)
			_guard->left = findSucceed(t);
		if (t == _guard->right)
			_guard->right = findFront(t);
		if (t->p == _guard) _root = tmp;///����Ǹ���Ҫ��ʱ���¸��ڵ�
		else if (t == t->p->left)///tmp ȡ��ԭ��t��λ��
			t->p->left = tmp;
		else
			t->p->right = tmp;
		tmp->p = t->p;
		if (t->color == black)///�����ɾ���Ľڵ��Ǻ�ɫ����Ҫ����������������
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
		//���ݹ�����������ǽڵ��Ǻ�ɫ
		while (tmp->color==red)
		{
			//��������������۵ĵ�����ڵ������ӵ�ʱ��
			if (tmp == tmp->p->left)
			{
				Pbra = tmp->p->right;
				///��һ����� �����Ǻ�ɫ
				if (Pbra!=_guard&&Pbra->color == red)
				{
					tmp->color = black;
					tmp->p->color = red;
					Pbra->color = black;
					t = tmp->p;//��ǰ�ڵ����游�ڵ�
					tmp = t->p;//ͬʱ���¸��ڵ�Ϊ�游�ڵ�ĸ��׽ڵ�
				}
				else
				{
					///�����Ǻ�ɫ
					if (t == tmp->right)///����ڵ����Һ��ӣ���������ɵ��������
					{
						Left_Rotate(tmp);
						tmp = t;//ע����������֮�󣬺��Ӹ��׽�ɫ����
					}
					tmp->color = black;//tmp��ɫ��ڣ��ﵽ��ѭ��������
					tmp->p->color = red;
					Right_Rotate(tmp->p);
				}							
			}
			else//����ǲ���ڵ����Һ��ӵ�������������ǶԳƵ�
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
			if (tmp==_guard)//˵����ǰ�ڵ��Ǹ��ڵ㣬��Ϊֻ�и��ڵ�ĸ��ڵ��Ǳ߽�ڵ�_guard
			{
				///������ʵ����ֱ�ӽ�t����ɫ��ɺ�ɫ��Ȼ��ֱ�ӳ�ѭ��
				tmp = t;
				tmp->color = black;
			}
		}		
	}

	///ɾ���ڵ�������������������������
	template<class T, class keycompare>
	void RBTree<T, keycompare>::RBDELETE_Fixup(RB_TreeNode<T> * t)
	{
		RB_TreeNode<T> * w = NULL;
		while (t!=_root&&t->color==black)
		{
			////Ҫ���ӵĺ��ӽڵ������ӵ����
			if (t == t->p->left)
			{
				w = t->p->right;//�ֵܽڵ�
				////��һ�����
				if (w->color == red)///�ֵ��Ǻ�ɫ
				{
					///�����ֵ��븸�׵���ɫ����Ϊ�ֵ���ɫ�Ǻ�ɫ�����׿϶��Ǻ�ɫ������ֱ�Ӹ�ֵ
					t->p->color = red;
					w->color = black;
					Left_Rotate(t->p);
				}
				else
				{
					///�ֵ��Һ����Ǻ�ɫ�����ǵ��������
					if (w->right->color == red)
					{
						w->color = t->p->color;
						t->p->color = black;
						w->right->color = black;
						Left_Rotate(t->p);
						t = _root;///������Ϊ�����һ�䣬��ѭ����Ҫ��tȾ�ɺ�ɫ����t����Ϊ���ڵ㣬���Գ�ѭ���������ڵ�Ⱦ��ûӰ��
					}
					else if (w->left->color == red)///�Һ����Ǻ�ɫ�����Ӻ�ɫ
					{
						w->color = red;
						w->left->color = black;
						Right_Rotate(w);
						w = w->p;//����������֮������ֵ�
					}
					else
					{
						///�������Ӷ��Ǻ�ɫ��Ҳ���ǵڶ�����������ֵ�Ⱦ�죬����һ�غ�ɫ�����ƣ�Ҳ���Ǹ��׽ڵ�
						w->color = red;
						t = t->p;
					}

				}
			}
			///����ǵ�ǰ�ڵ����Һ��ӵ���� ��ȫ�Գ�
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
		t->color = black;///��ѭ��Ҫô��t�Ǻ�ɫ��Ҫôt�Ǹ��ڵ㣬ֱ��Ⱦ�ڡ�
	}
	
    /////��beginRootΪ����������ʼѰ�ҽڵ�
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

	///////Ѱ��ǰ��
	template<class T, class keycompare>
	RB_TreeNode<T>* RBTree<T, keycompare>::findFront(RB_TreeNode<T>* t)
	{
		return t->findFront(_guard);
	}

	/////Ѱ�Һ��
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



	////�Լ������õĺ���
	/////ǰ�����
	template<class T, class keycompare>
	void RBTree<T, keycompare>::pre_traverse()
	{

	}

	////�������
	template<class T, class keycompare>
	void RBTree<T, keycompare>::mid_traverse(T* pt)
	{
		RB_TreeNode<T> * p = _root;
		stack<RB_TreeNode<T> *> s;
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
				cout << p->key << " ";
			else
				*(pt++) = p->key;
			s.pop();
			p = p->right;
		}
		cout << endl;
	}

	/////�������
	template<class T, class keycompare>
	void RBTree<T, keycompare>::post_traverse() {

	}

	/////��α���
	template<class T, class keycompare>
	void RBTree<T, keycompare>::print() {
		RB_TreeNode<T> * pRoot = _root;
		if (!pRoot) return;
		vector<queue<RB_TreeNode<T> *> > vq(2);
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
			cout << endl;
			index = 1 - index;
		}
	}

	template<class T, class keycompare>
	void RBTree<T, keycompare>::printNode(RB_TreeNode<T> * outT) {
		if (outT == _guard) return ;
		cout << "[" << " " << "key:" << outT->key << " ";
		if (outT->color == 0)
			cout << "color:" << "red" << " ";
		else
			cout << "color:" << "black" << " ";
		if (outT->left != _guard)
			cout << "left:" << outT->left->key << " ";
		if (outT->right != _guard)
			cout << "right:" << outT->right->key << " ";
		if (outT->p != _guard)
			cout << "parent:" << outT->p->key << " ";
		cout << "]";
	}


template<typename T>
ostream& operator<<(ostream &out, RB_TreeNode<T> * outT)
{

	return out;
}

