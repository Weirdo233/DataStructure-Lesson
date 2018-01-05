#pragma once
#include "Stack.h"
#include "Link.h"
#include <assert.h>
//Linked-stack实例
template<typename T> 
class LStack : public Stack<T>
{
private:
	Link<T>* top;		//顶元素的指针
	int stackSize;		//元素个数	

public:
	LStack()
	{ top = NULL; stackSize = 0; }
	~LStack()
	{ clear(); }
	void clear()
	{
		while (top != NULL)		//从栈顶向下删除节点
		{
			Link<T>* temp = top;
			top = top->next;
			delete temp;
		}
		stackSize = 0;
	}

	void push(const T& it)
	{
		top = new Link<T>(it, top);
		stackSize++;
	}

	T pop()
	{
		assert(top != NULL);	//检查栈是否为空
		T it = top->element;
		Link<T>* itemp = top->next;
		delete top;
		top = itemp;
		stackSize--;
		return it;
	}

	const T& GetTopValue() const
	{
		assert(top != NULL);	//检查栈是否为空
		return top->element;
	}

	int GetLength() const
	{
		return stackSize;
	}

	void sort()
	{
		LStack tmpsta1;
		LStack tmpsta2;
		T curr;
		curr = pop();
		tmpsta1.push(curr);
		while (GetLength())
		{
			curr = pop();
			while (tmpsta1.GetLength() && tmpsta1.GetTopValue() > curr)
			{
				tmpsta2.push(tmpsta1.pop());	//Pop an element from sta1 into sta2
			}
			tmpsta1.push(curr);		//Push curr into the right position
			while (tmpsta2.GetLength())
			{
				tmpsta1.push(tmpsta2.pop());	//Pop all the rest elements from sta2 into sta1
			}								//Now elements in sta1 are sorted, top is the max
		}
		while (tmpsta1.GetLength())
		{
			push(tmpsta1.pop());		//Put them in the original stack, top is the min
		}
	}
};
