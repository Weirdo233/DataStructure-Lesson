#pragma once
#include "List.h"
#include <assert.h>

#define DEFALT_SIZE 64

template<typename T> 
class AList : public List<T>	//顺序表(array based list 或 sequential list)
{
private:
	int maxSize;		//顺序表的最大长度
	int listSize;		//当前顺序表的元素数目
	int currPos;		//当前元素的位置
	T* listArray;		//保存顺序表元素的数组
public:
	AList(int size = DEFALT_SIZE)
	{
		maxSize = size;
		listSize = 0;
		currPos = 0;
		listArray = new T[maxSize];
	}
	~AList(){ delete [] listArray; }
	
	//清空
	void clear()
	{
		delete[] listArray;
		listSize = 0;
		currPos = 0;
		listArray = new T[maxSize];    //重新创建一个数组
	}

	//当前位置（之前）插入
	void insert(const T& item)
	{
		assert(listSize < maxSize);//断言顺序表空间是否已满
		for (int i = listSize; i > currPos; i--)
			listArray[i] = listArray[i - 1];	//当前位置之后的所有元素向后移一步
		listArray[currPos] = item;
		listSize++;
	}
	
	//尾部插入
	void push_back(const T& item)
	{
		assert(listSize < maxSize);
		listArray[listSize] = item;		//给最后一个元素赋值
		listSize++;		//顺序表长度加1
	}
	
	//当前位置删除
	//返回删除元素的值
	T remove()
	{
		assert(currPos>=0 && currPos < listSize);	//当前位置在顺序表范围内
		T item = listArray[currPos];
		for (int i = currPos; i < listSize - 1; i++)//当前位置之后的所有元素向前移一步
			listArray[i] = listArray[i+1];
		listSize--;
		return item;
	}

	//重置当前位置到开头
	void MoveToStart() { currPos = 0; } 
	//移到结尾位置（最后一个元素的后一位）
	void MoveToEnd() { currPos = listSize; }
	//向前移动一步
	void prev() { if(currPos != 0) currPos--; }
	//向后移一步
	void next() { if(currPos < listSize) currPos++; }

	//返回顺序表的长度
	int GetLength() const { return listSize; }
	//返回当前位置(index)
	int GetCurrPos() const { return currPos; }

	//设置当前位置（index）
	void MoveToPos(int pos)
	{
		assert(pos >= 0 && pos <= listSize);
		currPos = pos;
	}
	const T& GetValue() const
	{
		assert(currPos >= 0 && currPos <= listSize);
		return listArray[currPos];
	}

};



