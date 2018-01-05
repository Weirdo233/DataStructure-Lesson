#pragma once
#include "List.h"
#include "DLink.h"
#include <assert.h>
#include <iostream>

template<typename T> 
class DLList : public List<T>
{
private:
	DLink<T> *head;		//ָ������ͷ���սڵ㣩��ָ��
	DLink<T> *tail;		//ָ������β���սڵ㣩��ָ��
	DLink<T> *curr;		//ǰ���ڵ��ָ��
	int listSize;		//����ĳ���
	
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
		while (head != NULL)//��ͷ���ɾ���ڵ�
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

	//�������Ԫ��
	void print()
	{
		for (this->MoveToStart(); this->GetCurrPos() < this->GetLength(); this->next())
			std::cout << this->GetValue() << std::endl;
	}
	void clear() { removeall(); init(); }

	//��ǰ�ڵ㣨֮ǰ������ڵ�
	void insert(const T& item)
	{
		curr->next = curr->next->prev = new DLink<T>(item, curr, curr->next);
		listSize++;
	}
	//ͷ������ڵ�
	void push_front(const T& item)
	{
		head->next = head->next->prev = new DLink<T>(item, head, head->next);
		listSize++;
	}

	//β������ڵ�
	void push_back(const T& item)
	{
		tail->prev = tail->prev->next = new DLink<T>(item, tail->prev, tail);
		listSize++;
	}
	//ɾ����ǰ�ڵ㣨֮ǰ���Ľڵ�
	T remove()
	{
		assert(curr->next != NULL);
		if(curr->next == tail)
			return NULL;
		T it = curr->next->element;		//����ɾ����ֵ
		DLink<T> *Itemp = curr->next;	//����ɾ���Ľڵ�ָ��
		curr->next->next->prev = curr;
		curr->next = curr->next->next;
		delete Itemp;		//����delete�����
		listSize--;
		return it;
	}
	//��������ͷ
	void MoveToStart()
	{ curr = head; }
	//��������β
	void MoveToEnd()
	{ curr = tail; }
	//��ǰ�ƶ�һ��
	//�����ǰ�ڵ�������ͷ�򲻱�
	void prev()
	{ 
		if(curr != head)
			curr = curr->prev;
	}
	//����ƶ�һ��
	//�����ǰ�ڵ�������β�򲻱�
	void next()
	{
		if(curr != tail)
			curr = curr->next;
	}
	//����������
	int GetLength() const
	{ return listSize; }
	//���ص�ǰ�ڵ��λ��(index)
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

	//ͨ��ǰ���ڵ������ʵ�ǰ�ڵ��ֵ
	const T& GetValue() const
	{
		assert(curr->next != NULL);
		if(curr->next != tail)
			return curr->next->element;
		return NULL;
	}

	//���õ�ǰ�ڵ��ֵ
	void SetValue(T item)
	{
		curr->next->element = item;
	}

	//����
	void Bouble_Sort()
	{
		DLink<T> *i,*j;
		for (i = head->next; i != tail; i = i->next)
		{
			for (j = i; j != tail; j = j->next)
			{
				if (j->element < i->element)//���������ڵ������
				{
					T temp = j->element;
					j->element = i->element;
					i->element = temp;
				}
			}
		}
	}

	//ƴ��������������??
	static DLList<T> Sorted_Cat(DLList<T>& l1, DLList<T>& l2)
	{
		DLList<T> tmp;	//��������
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
				tmp.push_back(l1.GetValue());	//С�Ǹ�ͷԪ�صļ�����������
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
			tmp.tail->next = l2.curr->next;	//������1�Ѿ���ȡ���ˣ�ֱ�Ӱ�����2ʣ�µĽڵ�ŵ����������
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

	//���ñ��е�Ԫ��
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