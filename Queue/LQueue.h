#pragma once
#include "Link.h"
#include "Queue.h"
#include <assert.h>

template<typename T>
class LQueue : public Queue<T>
{
private:
	Link<T>* front;
	Link<T>* rear;
	int queueSize;
public:
	LQueue()
	{
		front = rear = new Link<T>;
		queueSize = 0;
	}
	~LQueue()
	{
		clear(); delete front;
	}

	//Ϊ�α���β�ڵ�??
	//��List����ɾ��ȫ���ڵ���newһ��ͷ�ڵ㣩
	void clear()
	{
		while (front->next != NULL)		//��ͷ���ɾ���ڵ�
		{
			rear = front;
			front = front->next;
			delete rear;
		}
		rear = front;
		queueSize = 0;
	}

	void enqueue(const T& it)
	{
		rear->next = new Link<T>(it, NULL);
		rear = rear->next;
		queueSize++;
	}

	T dequeue()
	{
		assert(queueSize != 0);
		T it = front->next->element;
		Link<T>* ittemp = front->next;
		front->next = front->next->next;
		if(rear == ittemp) rear = front;	//��ɾ���������һ��Ԫ�أ���front����rear
		delete ittemp;
		queueSize--;
		return it;
	}

	const T& GetFrontValue() const
	{
		assert(queueSize != 0);
		return front->next->element;
	}

	int GetLength() const
	{ return queueSize; }
};
