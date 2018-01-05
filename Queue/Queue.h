#pragma once
//Queue�����
template<typename T> 
class Queue
{
public:
	Queue() {}
	virtual ~Queue() {}

	virtual void clear() = 0;
	//��Ӳ���
	virtual void enqueue(const T& it) = 0;

	//���Ӳ���
	virtual T dequeue() = 0;

	virtual const T& GetFrontValue() const = 0;

	virtual int GetLength() const =  0;
};