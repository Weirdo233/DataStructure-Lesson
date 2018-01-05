#pragma once
#include "Stack.h"
#include <assert.h>

#define DEFAULT_SIZE 16

// Array-based stack
template <typename T>
class AStack : public Stack<T>
{
private:
	int maxSize;
	int top;	//��Ԫ�ص�����
	T* stackArray;
public:
	AStack(int size = DEFAULT_SIZE)
	{
		maxSize = size; top = -1; stackArray = new T[size];
	}
	~AStack()
	{ delete [] stackArray; }
	
	void clear()
	{
		top = -1;
	}

	void push(const T& it)
	{
		assert((top+1) != maxSize);		//判断栈是否已�?
		top++;
		stackArray[top] = it;
	}

	T pop()
	{
		assert(top != -1);		//判断栈是否为�?
		T temp = stackArray[top];
		top--;
		return temp;	//返回被删除的元素的�?
	}

	const T& GetTopValue() const
	{
		assert(top != -1);		//判断栈是否为�?
		return stackArray[top];
	}

	int GetLength() const
	{ return top+1; }
};