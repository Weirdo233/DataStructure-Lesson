#pragma once
//Doubly linked list（双向链表） 的 Node（节点）类的定义
template<typename T> 
class DLink
{
private:
	static DLink<T>* freelist;
public:
	T element;		//节点的值
	DLink* next;	//指向下个节点的指针
	DLink* prev;	//指向前一个节点的指针
	DLink(const T& elemval, DLink* prevval = NULL, DLink* nextval = NULL)
	{
		element = elemval;
		next = nextval;
		prev = prevval;
	}
	DLink(DLink* prevval = NULL, DLink* nextval = NULL)
	{ next = nextval; prev = prevval; }
	
	const DLink<T>& operator= (const DLink<T>& r)
	{
		element = r.element;
		next = r.next;
		prev = r.prev;
		return *this;
	}

	void* operator new(size_t size)		//重载new运算符
	{
		if(freelist == NULL)
			return ::new DLink;
		DLink<T>* temp = freelist;		//将节点从freelist中提取使用
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		//把删除的节点放到freelist首端
		((DLink<T>*)ptr)->next = freelist;
		freelist = (DLink<T>*)ptr;
	}
};

//freelist的头指针在此创建
template <typename T>
DLink<T>* DLink<T>::freelist = NULL;