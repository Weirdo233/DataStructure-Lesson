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
	int top;	//顶元素的索引
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
		assert((top+1) != maxSize);		//鍒ゆ柇鏍堟槸鍚﹀凡婊?
		top++;
		stackArray[top] = it;
	}

	T pop()
	{
		assert(top != -1);		//鍒ゆ柇鏍堟槸鍚︿负绌?
		T temp = stackArray[top];
		top--;
		return temp;	//杩斿洖琚垹闄ょ殑鍏冪礌鐨勫�?
	}

	const T& GetTopValue() const
	{
		assert(top != -1);		//鍒ゆ柇鏍堟槸鍚︿负绌?
		return stackArray[top];
	}

	int GetLength() const
	{ return top+1; }
};