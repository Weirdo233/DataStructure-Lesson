#pragma once
//Queue�����
template<typename T> 
class DQueue
{
public:
	DQueue() {}
	virtual ~DQueue() {}

	virtual void clear() = 0;
	//ͷ��Ӳ���
	virtual void enqueue_front(const T& it) = 0;
	//
	virtual void enqueue_back(const T& it) = 0;
	//ͷ���Ӳ���
	virtual T dequeue_front() = 0;
	
	virtual T dequeue_back() = 0;

	virtual const T& GetFrontValue() const = 0;

	virtual const T& GetRearValue() const = 0;

	virtual int GetLength() const =  0;
};