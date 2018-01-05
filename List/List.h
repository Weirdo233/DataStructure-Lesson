#pragma once
template<typename T>
class List		//虚基类List
{
public:
	List() {};
	~List() {};

	//清空List的元素
	virtual void clear() = 0;
	
	//在List的当前位置插入一个元素
	virtual void insert(const T& item) = 0;

	//在尾部添加一个元素
	virtual void push_back(const T& item) = 0;

	//删除当前位置的元素并返回其值
	virtual T remove() = 0;

	//将当前位置设为首元素
	virtual void MoveToStart() = 0;

	//将当前位置设为尾元素
	virtual void MoveToEnd() = 0;

	//将当前位置向左移一步
	//如果当前为首元素则不变
	virtual void prev() = 0;

	//将当前位置向右移一步
	//如果当前为尾元素则不变
	virtual void next() = 0;

	//返回List中元素的个数
	virtual int GetLength() const  = 0;

	//返回当前元素的位置
	virtual int GetCurrPos() const = 0;

	//返回当前元素的值
	virtual const T& GetValue() const = 0;

	////设置当前元素的值
	//virtual void SetValue(T item) = 0; 
	
	//设置当前位置
	virtual void MoveToPos(int pos) = 0;
};


