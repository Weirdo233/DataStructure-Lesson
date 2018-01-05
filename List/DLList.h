#pragma once
#include "List.h"
#include "DLink.h"
#include <assert.h>
#include <iostream>

template<typename T> 
class DLList : public List<T>
{
private:
	DLink<T> *head;		//指向链表头（空节点）的指针
	DLink<T> *tail;		//指向链表尾（空节点）的指针
	DLink<T> *curr;		//前驱节点的指针
	int listSize;		//链表的长度
	
public:
	void init()
	{
		curr = head = new DLink<T>;
		head->next = tail = new DLink<T>(NULL, head->next);
		tail->prev = head;
		listSize = 0;
	}

	void removeall()
	{
		while (head != NULL)//从头向后删除节点
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}

	DLList() { init(); }
	DLList(const DLList<T>& llist)
	{
		init();
		head = llist.head;
		tail = llist.tail;
		listSize = llist.listSize;
	}
	~DLList() { removeall(); }

	const DLList<T>& operator=(const DLList<T>& llist)
	{
		removeall();
		init();
		head = llist.head;
		tail = llist.tail;
		listSize = llist.listSize;
		return *this;
	}

	//输出所有元素
	void print()
	{
		for (this->MoveToStart(); this->GetCurrPos() < this->GetLength(); this->next())
			std::cout << this->GetValue() << std::endl;
	}
	void clear() { removeall(); init(); }

	//当前节点（之前）插入节点
	void insert(const T& item)
	{
		curr->next = curr->next->prev = new DLink<T>(item, curr, curr->next);
		listSize++;
	}
	//头部插入节点
	void push_front(const T& item)
	{
		head->next = head->next->prev = new DLink<T>(item, head, head->next);
		listSize++;
	}

	//尾部插入节点
	void push_back(const T& item)
	{
		tail->prev = tail->prev->next = new DLink<T>(item, tail->prev, tail);
		listSize++;
	}
	//删除当前节点（之前）的节点
	T remove()
	{
		assert(curr->next != NULL);
		if(curr->next == tail)
			return NULL;
		T it = curr->next->element;		//保存删除的值
		DLink<T> *Itemp = curr->next;	//保存删除的节点指针
		curr->next->next->prev = curr;
		curr->next = curr->next->next;
		delete Itemp;		//重载delete运算符
		listSize--;
		return it;
	}
	//移至链表头
	void MoveToStart()
	{ curr = head; }
	//移至链表尾
	void MoveToEnd()
	{ curr = tail; }
	//向前移动一步
	//如果当前节点是链表头则不变
	void prev()
	{ 
		if(curr != head)
			curr = curr->prev;
	}
	//向后移动一步
	//如果当前节点是链表尾则不变
	void next()
	{
		if(curr != tail)
			curr = curr->next;
	}
	//返回链表长度
	int GetLength() const
	{ return listSize; }
	//返回当前节点的位置(index)
	int GetCurrPos() const
	{
		DLink<T> *temp = head;
		int i;
		for (i = 0; temp != curr; i++)
			temp = temp->next;
		return i;
	}

	//
	void MoveToPos(int n)
	{
		assert(n >= 0 && n <= listSize);
		curr = head;
		for(int i = 0;i < n; i++)
			curr = curr->next;
	}

	//通过前驱节点来访问当前节点的值
	const T& GetValue() const
	{
		assert(curr->next != NULL);
		if(curr->next != tail)
			return curr->next->element;
		return NULL;
	}

	//设置当前节点的值
	void SetValue(T item)
	{
		curr->next->element = item;
	}

	//排序
	void Bouble_Sort()
	{
		DLink<T> *i,*j;
		for (i = head->next; i != tail; i = i->next)
		{
			for (j = i; j != tail; j = j->next)
			{
				if (j->element < i->element)//交换两个节点的数据
				{
					T temp = j->element;
					j->element = i->element;
					i->element = temp;
				}
			}
		}
	}

	//拼接两个有序链表??
	static DLList<T> Sorted_Cat(DLList<T>& l1, DLList<T>& l2)
	{
		DLList<T> tmp;	//最终链表
		l1.MoveToStart();
		l2.MoveToStart();
		if (l1.GetValue() < l2.GetValue())
		{
			tmp.push_back(l1.GetValue());
			l1.next();
		}
		else
		{
			tmp.push_back(l2.GetValue());
			l2.next();
		}
		while (l1.GetCurrPos() < l1.GetLength() && l2.GetCurrPos() < l2.GetLength())	
		{
			if (l1.GetValue() < l2.GetValue())
			{
				tmp.push_back(l1.GetValue());	//小那个头元素的加入最终链表
				l1.next();
			}
			else
			{
				tmp.push_back(l2.GetValue());
				l2.next();
			}
		}
		if (l1.GetCurrPos() == l1.GetLength())
		{
			tmp.tail->next = l2.curr->next;	//若链表1已经提取完了，直接把链表2剩下的节点放到最终链表后
			tmp.tail = l2.tail;
			tmp.listSize += l2.GetLength() - l2.GetCurrPos();
		}
		else 
		{
			tmp.tail->next = l1.curr->next;
			tmp.tail = l1.tail;
			tmp.listSize += l1.GetLength() - l1.GetCurrPos();
		}
		return tmp;
	}

	//倒置表中的元素
	void reverse()
	{
		for (DLink<T>* start = head->next, *end = tail->prev;
			start->prev->prev != end && start->prev != end;
			start = start->next, end = end->prev)
		{
			T temp;
			temp = start->element;
			start->element = end->element;
			end->element = temp;
		}
	}
};