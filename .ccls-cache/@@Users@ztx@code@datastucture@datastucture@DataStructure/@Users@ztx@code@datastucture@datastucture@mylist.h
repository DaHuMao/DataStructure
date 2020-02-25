#pragma once
#include<iostream>
#include<vector>
using namespace std;
struct List{
	int val;
	List* next;
	List(int a) :val(a), next(NULL) {};
};
class myList
{
public:
	myList(vector<int>& v)
	{
		if (v.empty())
		{
			_head = NULL;
			return;
		}
		_head = new List(v[0]);
		List* tmp = _head;
		for (int i = 1; i < v.size(); i++)
		{
			List* p = new List(v[i]);
			tmp->next = p;
			tmp = p;
		}
    }
	myList(int* p)
	{

	}
	myList(List* P)
	{
		_head = P;
	}
	~myList()
	{
		while (_head)
		{
			List* tmp = _head;
			_head = _head->next;
			delete(tmp);
		}
	}
	List* gethead()
	{
		return _head;
	}
	void sethead(List* head)
	{
		_head = head;
	}
	List* mergesort(List* head)
	{
		if (!head || !head->next) return head;
		List* slow = head;
		List* fast = head->next;
		while (fast&&fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		fast = slow;
		slow = slow->next;
		fast->next = NULL;
		fast = mergesort(head);
		slow = mergesort(slow);
		return Listsort(fast, slow);
		
	}
	List* Listsort(List* head1, List* head2)
	{
		if (!head1) return head2;
		if (!head2) return head1;
		List* head, *p;		
		if (head1->val < head2->val)
		{
			head = head1;
			head1 = head1->next;
		}
		else
		{
			head = head2;
			head2 = head2->next;
		}	
		p = head;
		while (head1&&head2)
		{
			if (head1->val < head2->val)
			{
				p->next = head1;
				head1 = head1->next;
			}
			else
			{
				p->next = head2;
				head2 = head2->next;
			}
			p = p->next;
		}
		if (!head1) p->next = head2;
		else p->next = head1;
		return head;	    
	}
	void print()
	{
		List* head = _head;
		while (head)
		{
			cout << head->val<<" ";
			head = head->next;
		}
		cout << endl;
	}
private:
	List* _head;
};
