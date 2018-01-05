#pragma once
//Node���ڵ㣩��Ķ���
//��֧��Freelist�������ÿռ��
template<typename T> 
class Link
{
private:
	static Link<T>* freelist;
public:
	T element;		//�ڵ��ֵ
	Link* next;		//ָ���¸��ڵ��ָ��
					//β�ڵ��nextָ����ָ��β�ڵ�
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

	void* operator new(size_t size)		//����new�����
	{
		if(freelist == NULL)
			return ::new Link;
		Link<T>* temp = freelist;		//���ڵ��freelist����ȡʹ��
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		//��ɾ���Ľڵ�ŵ�freelist�׶�
		((Link<T>*)ptr)->next = freelist;
		freelist = (Link<T>*)ptr;
	}
};

//freelist��һ��NULL��Linkָ��
template <typename T>
Link<T>* Link<T>::freelist = NULL;