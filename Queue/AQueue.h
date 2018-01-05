#pragma once
#include "Queue.h"
#include <assert.h>
#define	DEFAULT_SIZE 16

//Array-based Queue ??
template<typename T> 
class AQueue : public Queue<T>
{
private:
	int maxSize;	//���е���󳤶�
	int front;		//ͷԪ�ص�����
	int rear;		//βԪ�ص�����
	T* listArray;	
	
public:
	AQueue(int size = DEFAULT_SIZE)
	{
		maxSize = size + 1;		//�����ʵ�ʴ�С����󳤶ȴ�1
		rear = 0;
		front = 1;
		listArray = new T[maxSize];
	}

	~AQueue() { delete [] listArray; }

	void clear() { rear = 0; front = 1; }
	
	void enqueue(const T& it)
	{
		assert((rear+2) % maxSize != front);	//�ж϶����Ƿ�����
		rear = (rear+1) % maxSize; 
		listArray[rear] = it;
	}

	T dequeue()
	{
		assert(GetLength() != 0);
		T it = listArray[front];
		front = (front+1) % maxSize;
		return it;
	}

	const T& GetFrontValue() const
	{
		assert(GetLength() != 0);
		return listArray[front];
	}

	int GetLength() const
	{
		return ((rear + maxSize) - front + 1) % maxSize;
	}
};