#pragma once
template<typename T>
class List		//�����List
{
public:
	List() {};
	~List() {};

	//���List��Ԫ��
	virtual void clear() = 0;
	
	//��List�ĵ�ǰλ�ò���һ��Ԫ��
	virtual void insert(const T& item) = 0;

	//��β�����һ��Ԫ��
	virtual void push_back(const T& item) = 0;

	//ɾ����ǰλ�õ�Ԫ�ز�������ֵ
	virtual T remove() = 0;

	//����ǰλ����Ϊ��Ԫ��
	virtual void MoveToStart() = 0;

	//����ǰλ����ΪβԪ��
	virtual void MoveToEnd() = 0;

	//����ǰλ��������һ��
	//�����ǰΪ��Ԫ���򲻱�
	virtual void prev() = 0;

	//����ǰλ��������һ��
	//�����ǰΪβԪ���򲻱�
	virtual void next() = 0;

	//����List��Ԫ�صĸ���
	virtual int GetLength() const  = 0;

	//���ص�ǰԪ�ص�λ��
	virtual int GetCurrPos() const = 0;

	//���ص�ǰԪ�ص�ֵ
	virtual const T& GetValue() const = 0;

	////���õ�ǰԪ�ص�ֵ
	//virtual void SetValue(T item) = 0; 
	
	//���õ�ǰλ��
	virtual void MoveToPos(int pos) = 0;
};


