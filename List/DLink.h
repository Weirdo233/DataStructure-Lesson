#pragma once
//Doubly linked list��˫������ �� Node���ڵ㣩��Ķ���
template<typename T> 
class DLink
{
private:
	static DLink<T>* freelist;
public:
	T element;		//�ڵ��ֵ
	DLink* next;	//ָ���¸��ڵ��ָ��
	DLink* prev;	//ָ��ǰһ���ڵ��ָ��
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

	void* operator new(size_t size)		//����new�����
	{
		if(freelist == NULL)
			return ::new DLink;
		DLink<T>* temp = freelist;		//���ڵ��freelist����ȡʹ��
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		//��ɾ���Ľڵ�ŵ�freelist�׶�
		((DLink<T>*)ptr)->next = freelist;
		freelist = (DLink<T>*)ptr;
	}
};

//freelist��ͷָ���ڴ˴���
template <typename T>
DLink<T>* DLink<T>::freelist = NULL;