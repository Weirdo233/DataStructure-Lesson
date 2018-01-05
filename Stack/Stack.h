#pragma once
//–Èª˘¿‡Stack
template <typename T> 
class Stack
{
public:
	Stack() {};
	virtual ~Stack() {};

	virtual void clear() = 0;

	virtual void push(const T& it) = 0;
	virtual T pop() = 0;
	virtual const T& GetTopValue() const = 0;
	virtual int GetLength() const = 0;
};