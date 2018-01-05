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

	//为何保留尾节点??
	//（List中是删除全部节点再new一个头节点）
	void clear()
	{
		while (front->next != NULL)		//从头向后删除节点
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
		if(rear == ittemp) rear = front;	//若删除的是最后一个元素，把front赋给rear
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
