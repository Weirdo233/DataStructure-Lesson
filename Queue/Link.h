#pragma once
//Node（节点）类的定义
//并支持Freelist（可利用空间表）
template<typename T> 
class Link
{
private:
	static Link<T>* freelist;
public:
	T element;		//节点的值
	Link* next;		//指向下个节点的指针
					//尾节点的next指针仍指向尾节点
	Link(const T& elemval, Link* nextval = NULL)
	{
		element = elemval;
		next = nextval;
	}
	Link(Link* nextval = NULL)
	{ next = nextval; }
	
	const Link<T>& operator= (const Link<T>& r)
	{
		element = r.element;
		next = r.next;
		return *this;
	}

	void* operator new(size_t size)		//重载new运算符
	{
		if(freelist == NULL)
			return ::new Link;
		Link<T>* temp = freelist;		//将节点从freelist中提取使用
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		//把删除的节点放到freelist首端
		((Link<T>*)ptr)->next = freelist;
		freelist = (Link<T>*)ptr;
	}
};

//freelist是一个NULL的Link指针
template <typename T>
Link<T>* Link<T>::freelist = NULL;