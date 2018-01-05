#pragma once
#include "List.h"
#include "Link.h"
#include <assert.h>
#include <iostream>

#define DEFAULT_SIZE 32

template<typename T> 
class LList : public List<T>
{
private:
	Link<T> *head;		//指向链表头（空节点）的指针
	Link<T> *tail;		//指向链表尾的指针
	Link<T> *curr;		//前驱节点的指针
	int listSize;		//链表的长度
	
public:
	void init()
	{
		curr = tail = head = new Link<T>;
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

	LList() { init(); }
	LList(const LList<T>& llist)
	{
		init();
		head = llist.head;
		tail = llist.tail;
		listSize = llist.listSize;
	}
	~LList() { removeall(); }

	const LList<T>& operator=(const LList<T>& llist)
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
		curr->next = new Link<T>(item, curr->next);
		if(tail == curr) tail = curr->next;
		listSize++;
	}
	////头部插入节点
	//void push_front(const T& item)
	//{
	//	Link<T> *temp = head;//保存表头的值
	//	head = new Link<T>(item, NULL);
	//	head->next = temp;
	//}

	//尾部插入节点
	void push_back(const T& item)
	{
		tail = tail->next = new Link<T>(item, NULL);		//尾节点的next指针仍指向尾节点
		listSize++;
	}
	//删除当前节点（curr的下一个）的节点
	T remove()
	{
		assert(curr->next != NULL);
		T it = curr->next->element;		//保存删除的值
		Link<T> *Itemp = curr->next;	//保存删除的节点指针
		if(tail == curr->next) tail = curr;
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
	{ MoveToPos(listSize - 1); }
	//向前移动一步
	//如果当前节点是链表头则不变
	void prev()
	{ 
		if(curr == head) return;
		//遍历链表以找到前一个节点
		Link<T> *temp = head;
		while(temp->next != curr)
			temp = temp->next;
		curr = temp;
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
		Link<T> *temp = head;
		int i;
		for (i = 0; temp != curr; i++)
			temp = temp->next;
		return i;
	}

	//移动到n位置(index)
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
		return curr->next->element;
	}

	//设置当前节点的值
	void SetValue(T item)
	{
		curr->element = item;
	}

	//排序
	void Bouble_Sort()
	{
		Link<T> *i,*j;
		for (i = head->next; i != NULL; i = i->next)
		{
			for (j = i; j != NULL; j = j->next)
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
	static void Sorted_Cat(LList<T>& l1, LList<T>& l2, LList<T>& tmp)
	{
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
		return ;
	}

	//倒置表中的元素
	void Reverse()
	{
		//从头向后把每个元素插入到首位
		if(listSize == 0) return;
		Link<T>* current = head->next->next;	//第二个节点开始
		Link<T>* tmp;
		tail = head->next;
		while (current != NULL)
		{
			tmp = current;
			current = current->next;

			tmp->next = head->next;	//节点放到表头后（首位置）
			head->next = tmp;		
		}
		return;
	}
};