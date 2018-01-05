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
	Link<T> *head;		//ָ������ͷ���սڵ㣩��ָ��
	Link<T> *tail;		//ָ������β��ָ��
	Link<T> *curr;		//ǰ���ڵ��ָ��
	int listSize;		//����ĳ���
	
public:
	void init()
	{
		curr = tail = head = new Link<T>;
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
		curr->next = new Link<T>(item, curr->next);
		if(tail == curr) tail = curr->next;
		listSize++;
	}
	////ͷ������ڵ�
	//void push_front(const T& item)
	//{
	//	Link<T> *temp = head;//�����ͷ��ֵ
	//	head = new Link<T>(item, NULL);
	//	head->next = temp;
	//}

	//β������ڵ�
	void push_back(const T& item)
	{
		tail = tail->next = new Link<T>(item, NULL);		//β�ڵ��nextָ����ָ��β�ڵ�
		listSize++;
	}
	//ɾ����ǰ�ڵ㣨curr����һ�����Ľڵ�
	T remove()
	{
		assert(curr->next != NULL);
		T it = curr->next->element;		//����ɾ����ֵ
		Link<T> *Itemp = curr->next;	//����ɾ���Ľڵ�ָ��
		if(tail == curr->next) tail = curr;
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
	{ MoveToPos(listSize - 1); }
	//��ǰ�ƶ�һ��
	//�����ǰ�ڵ�������ͷ�򲻱�
	void prev()
	{ 
		if(curr == head) return;
		//�����������ҵ�ǰһ���ڵ�
		Link<T> *temp = head;
		while(temp->next != curr)
			temp = temp->next;
		curr = temp;
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
		Link<T> *temp = head;
		int i;
		for (i = 0; temp != curr; i++)
			temp = temp->next;
		return i;
	}

	//�ƶ���nλ��(index)
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
		return curr->next->element;
	}

	//���õ�ǰ�ڵ��ֵ
	void SetValue(T item)
	{
		curr->element = item;
	}

	//����
	void Bouble_Sort()
	{
		Link<T> *i,*j;
		for (i = head->next; i != NULL; i = i->next)
		{
			for (j = i; j != NULL; j = j->next)
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
		return ;
	}

	//���ñ��е�Ԫ��
	void Reverse()
	{
		//��ͷ����ÿ��Ԫ�ز��뵽��λ
		if(listSize == 0) return;
		Link<T>* current = head->next->next;	//�ڶ����ڵ㿪ʼ
		Link<T>* tmp;
		tail = head->next;
		while (current != NULL)
		{
			tmp = current;
			current = current->next;

			tmp->next = head->next;	//�ڵ�ŵ���ͷ����λ�ã�
			head->next = tmp;		
		}
		return;
	}
};