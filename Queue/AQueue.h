#pragma once
#include "Queue.h"
#include <assert.h>
#define	DEFAULT_SIZE 16

//Array-based Queue ??
template<typename T> 
class AQueue : public Queue<T>
{
private:
	int maxSize;	//队列的最大长度
	int front;		//头元素的索引
	int rear;		//尾元素的索引
	T* listArray;	
	
public:
	AQueue(int size = DEFAULT_SIZE)
	{
		maxSize = size + 1;		//数组的实际大小比最大长度大1
		rear = 0;
		front = 1;
		listArray = new T[maxSize];
	}

	~AQueue() { delete [] listArray; }

	void clear() { rear = 0; front = 1; }
	
	void enqueue(const T& it)
	{
		assert((rear+2) % maxSize != front);	//判断队列是否已满
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