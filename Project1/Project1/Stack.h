#pragma once
#include <iostream>
using namespace std;

#define maxStack 100


/**
*   @brief   Exception class thrown by Push when stack is full.
*/
class FullStack
{
public:
	/**
	*   @brief   Display a message for full stack on screen.
	*/
	void print()
	{
		cout << "FullStack exception thrown." << endl;
	}
};


/**
*   @brief   Exception class thrown by Pop and Top when stack is empty.
*/
class EmptyStack
{
public:
	/**
	*   @brief   Display a message for full stack on screen.
	*/
	void print()
	{
		cout << "EmtpyStack exception thrown." << endl;
	}
};


/**
*   @brief   Stack class.
*   @details   This class processes as Last In, First Out (LIFO).
*/
template <typename T>
class Stack
{
public:

	/**
	*   @brief   MaxAllocate dynamic array whose size is maxStack.
	*   @pre   The maxStack is defined
	*   @post   Member of items points the allocated array.
	*/
	Stack();

	Stack(const Stack<T>& stack);

	/**
	*   @brief   Destruct the object. Free the array dynamically allocated.
	*   @pre   Release memory for stack pointer.
	*   @post   none.
	*/
	~Stack();

	/**
	*   @brief   ������ ���ִ��� Ȯ��.
	*   @pre   ������ �ʱ�ȭ �Ǿ��ִ�.
	*   @post   Function value = (stack is full)
	*/
	bool IsFull() const;

	/**
	*   @brief   ������ ����ִ��� Ȯ��.
	*   @pre   ������ �ʱ�ȭ �Ǿ��ִ�.
	*   @post   Function value = (stack is empty)
	*/
	bool IsEmpty() const;

	/**
	*   @brief ������ top�� ���ο� ������ �߰�.
	*   @pre   ������ �ʱ�ȭ �Ǿ��ִ�.
	*   @post   If (stack is full), FullStack exception is thrown; otherwise, newItem is at the top of the stack.
	*/
	void Push(T item);

	/**
	*   @brief   �������κ��� top�κ� ����.
	*   @pre   ������ �ʱ�ȭ �Ǿ��ִ�..
	*   @post   If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Pop();

	/**
	*   @brief   ������ top �����͸� �����ؼ� ��ȯ.
	*   @pre   ������ �ʱ�ȭ �Ǿ��ִ�.
	*   @post   If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Top();

	/**
	*   @brief   ��ũ���� ������ ��� ������ ���
	*   @pre   ������ �ʱ�ȭ �Ǿ��ִ�.
	*   @post   ����.
	*/
	void Print();
	/**
	*   @brief   ���Կ����� �����ε�
	*   @post   �Է¹��� ������ ��ī�ǵȴ�.
	*/
	Stack<T>& operator=(const Stack<T>& stack);
private:
	int top;   ///< Number of elements.
	T *items;   ///< Pointer for a stack.
};

//Maxsize�� 500���� �Ҵ�.
template <typename T>
Stack<T>::Stack()
{
	items = new T[maxStack];
	top = -1;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& stack)
{
	items = new T[maxStack];
	top = stack.top;
	for (int i = 0; i < maxStack; i++)
	{
		items = stack[i];
	}
}


// ���� �����Ҵ� Destruct the object. Free the array dynamically allocated.
template <typename T>
Stack<T>::~Stack()
{
	delete[] items;
}


//������ �� ���ִ��� Ȯ��.
template <typename T>
bool Stack<T>::IsEmpty() const
{
	if (top <= -1)
		return true;
	else
		return false;
}


//������ ����ִ��� Ȯ��.
template <typename T>
bool Stack<T>::IsFull() const
{
	if (top >= maxStack - 1)
		return true;
	else
		return false;
}

// ������ top�� ���ο� ������ �߰�.
template <typename T>
void Stack<T>::Push(T newItem)
{
	if (IsFull())
		throw FullStack();
	else
	{
		top++;
		items[top] = newItem;
	}
}

// ������ top�κ� ����
template <typename T>
T Stack<T>::Pop()
{
	T temp;

	if (IsEmpty())
		throw EmptyStack();
	else
	{
		temp = Top();
		top--;
		return temp;
	}
}


// ������ top�κ� ��ȯ
template <typename T>
T Stack<T>::Top()
{
	if (IsEmpty())
		throw EmptyStack();
	else
		return items[top];
}


// ��ũ���� ���ÿ� �����ϴ� ������ ���
template <typename T>
void Stack<T>::Print()
{
	cout << "Stack: ";
	// Stack ���� ��� element ���.
	for (int i = top; i >= 0; i--)
	{
		cout << items[i] << " - ";
	}
	cout << endl;
}

//���Կ����� �����ε�
template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
	items = new T[maxStack];
	top = stack.top;
	for (int i = 0; i < maxStack; i++)
	{
		items[i] = stack.items[i];
	}
	return *this;
}