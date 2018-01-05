#pragma once
#include "DLink.h"
#include "DQueue.h"
#include <assert.h>
#include <iostream>

template<typename T>
class DLQueue : public DQueue<T>
{
private:
	DLink<T>* front;		//ͷ���գ��ڵ�
	DLink<T>* rear;		//β���գ��ڵ�
	int queueSize;
public:
	DLQueue()
	{
		rear = new DLink<T>;
		front = new DLink<T>(0, NULL, rear);
		rear->prev = front;
		queueSize = 0;
	}
	~DLQueue()
	{
		clear(); delete front; delete rear;
	}

	//������нڵ㣨ͷβ���⣩
	void clear()
	{
		for (DLink<T>* curr = front->next, *temp = curr; temp != rear;)
		{
			curr = temp;
			temp = curr->next;
			delete curr;
		}
		front->next = rear;
		queueSize = 0;
	}

	void print()
	{
		std::cout << "The current elements are: ";
		DLink<T>* curr = front->next;
		for (; curr != rear; curr = curr->next)
			std::cout << curr->element << ' ';
		std::cout << std::endl;
	}

	void enqueue_front(const T& it)
	{
		front->next = front->next->prev = new DLink<T>(it, front, front->next);
		queueSize++;
	}

	void enqueue_back(const T& it)
	{
		rear->prev = rear->prev->next = new DLink<T>(it, rear->prev, rear);
		queueSize++;
	}

	T dequeue_front()
	{
		assert(queueSize != 0);
		T it = front->next->element;		//����ɾ����ֵ
		DLink<T> *Itemp = front->next;	//����ɾ���Ľڵ�ָ��
		front->next->next->prev = front;
		front->next = front->next->next;
		delete Itemp;		//����delete�����
		queueSize--;
		return it;
	}

	T dequeue_back()
	{
		assert(queueSize != 0);
		T it = rear->prev->element;		//����ɾ����ֵ
		DLink<T> *Itemp = rear->prev;	//����ɾ���Ľڵ�ָ��
		rear->prev->prev->next = rear;
		rear->prev = rear->prev->prev;
		delete Itemp;		//����delete�����
		queueSize--;
		return it;
	}

	const T& GetFrontValue() const
	{
		assert(queueSize != 0);
		return front->next->element;
	}

	const T& GetRearValue() const
	{
		assert(queueSize != 0);
		return rear->prev->element;
	}

	int GetLength() const
	{ return queueSize; }
};
