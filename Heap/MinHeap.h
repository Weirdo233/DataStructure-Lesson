#pragma once
#include <assert.h>
#include <iostream>

using namespace std;

//Min Heap class
template<typename T>
class MinHeap
{
private:
	T* heapArray;		//Pointer to the heap array
	int size;	//Number of elements in the heap
	int maxSize;	//Maximun size of the heap
	inline void swap(T* arr, int pos1, int pos2);

	//Sift down the element of index "pos" in the heap array
	void SiftDown(int pos)
	{
		int l = leftchild(pos);
		int r = rightchild(pos);
		int least = pos;
		if (l < size)			//Find the min in pos and its child nodes
			if (heapArray[l] < heapArray[least]) least = l;
		if (r < size)
			if (heapArray[r] < heapArray[least]) least = r;
		if (least != pos)
		{
			swap(heapArray, pos, least);
			if(!IsLeaf(least))
				SiftDown(least);
		}
	}
public:
	MinHeap(T* arr, int n, int max)
	{
		heapArray = arr; size = n; maxSize = max;
	}
	int GetSize() { return size; }
	bool IsLeaf(int pos)
	{
		if (pos < size && pos >= size / 2) return true;
		return false;
	}

	int leftchild(int pos) const
	{
		return 2 * pos + 1;
	}
	int rightchild(int pos) const
	{
		return 2 * pos + 2;
	}

	int parent(int pos) const
	{
		return (pos - 1) / 2;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
			cout << heapArray[i] << ' ';
		cout << endl;
	}

	void BuildHeap()		//"size/2-1" is the index 
							//of the last not-leaf node 
	{
		for (int i = size / 2 - 1; i >= 0; i--)
			SiftDown(i);
	}

	void insert(const T& it)
	{
		assert(size < maxSize);
		int curr = size;
		size++;
		heapArray[curr] = it;
		//sift up until curr's parent is smaller than curr
		while (curr != 0 && (heapArray[curr] < heapArray[parent(curr)]))
		{
			swap(heapArray, curr, parent(curr));
			curr = parent(curr);
		}
	}

	T RemoveFirst()
	{
		assert(size > 0);
		swap(heapArray, 0, size - 1);	//Swap the first and the last
		size--;		//Size-1
		if (size != 0) SiftDown(0);	//Sift down the new root node
		return heapArray[size];	//Return the deleted value
	}

	T Remove(int pos)
	{
		assert(pos >= 0 && pos < size);
		if (pos == (size - 1)) size--;
		else
		{
			swap(heapArray, pos, size - 1);		//Swap "pos" with the last
			size--;								//Then sift up
			while (pos != 0 && heapArray[pos] < heapArray[parent(pos)])
			{
				swap(heapArray, pos, parent(pos));
				pos = parent(pos);
			}
			if (size != 0)SiftDown(pos);
			return heapArray[size];
		}
	}
};

template<typename T>
inline void MinHeap<T>::swap(T* arr, int pos1, int pos2)
{
	T temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}