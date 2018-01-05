#pragma once
//Queue虚基类
template<typename T> 
class Queue
{
public:
	Queue() {}
	virtual ~Queue() {}

	virtual void clear() = 0;
	//入队操作
	virtual void enqueue(const T& it) = 0;

	//出队操作
	virtual T dequeue() = 0;

	virtual const T& GetFrontValue() const = 0;

	virtual int GetLength() const =  0;
};