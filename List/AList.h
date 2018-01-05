#pragma once
#include "List.h"
#include <assert.h>

#define DEFALT_SIZE 64

template<typename T> 
class AList : public List<T>	//˳���(array based list �� sequential list)
{
private:
	int maxSize;		//˳������󳤶�
	int listSize;		//��ǰ˳����Ԫ����Ŀ
	int currPos;		//��ǰԪ�ص�λ��
	T* listArray;		//����˳���Ԫ�ص�����
public:
	AList(int size = DEFALT_SIZE)
	{
		maxSize = size;
		listSize = 0;
		currPos = 0;
		listArray = new T[maxSize];
	}
	~AList(){ delete [] listArray; }
	
	//���
	void clear()
	{
		delete[] listArray;
		listSize = 0;
		currPos = 0;
		listArray = new T[maxSize];    //���´���һ������
	}

	//��ǰλ�ã�֮ǰ������
	void insert(const T& item)
	{
		assert(listSize < maxSize);//����˳���ռ��Ƿ�����
		for (int i = listSize; i > currPos; i--)
			listArray[i] = listArray[i - 1];	//��ǰλ��֮�������Ԫ�������һ��
		listArray[currPos] = item;
		listSize++;
	}
	
	//β������
	void push_back(const T& item)
	{
		assert(listSize < maxSize);
		listArray[listSize] = item;		//�����һ��Ԫ�ظ�ֵ
		listSize++;		//˳����ȼ�1
	}
	
	//��ǰλ��ɾ��
	//����ɾ��Ԫ�ص�ֵ
	T remove()
	{
		assert(currPos>=0 && currPos < listSize);	//��ǰλ����˳���Χ��
		T item = listArray[currPos];
		for (int i = currPos; i < listSize - 1; i++)//��ǰλ��֮�������Ԫ����ǰ��һ��
			listArray[i] = listArray[i+1];
		listSize--;
		return item;
	}

	//���õ�ǰλ�õ���ͷ
	void MoveToStart() { currPos = 0; } 
	//�Ƶ���βλ�ã����һ��Ԫ�صĺ�һλ��
	void MoveToEnd() { currPos = listSize; }
	//��ǰ�ƶ�һ��
	void prev() { if(currPos != 0) currPos--; }
	//�����һ��
	void next() { if(currPos < listSize) currPos++; }

	//����˳���ĳ���
	int GetLength() const { return listSize; }
	//���ص�ǰλ��(index)
	int GetCurrPos() const { return currPos; }

	//���õ�ǰλ�ã�index��
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



