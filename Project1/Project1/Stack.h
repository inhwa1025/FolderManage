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
	*   @brief   스택이 차있는지 확인.
	*   @pre   스택은 초기화 되어있다.
	*   @post   Function value = (stack is full)
	*/
	bool IsFull() const;

	/**
	*   @brief   스택이 비어있는지 확인.
	*   @pre   스택은 초기화 되어있다.
	*   @post   Function value = (stack is empty)
	*/
	bool IsEmpty() const;

	/**
	*   @brief 스택의 top에 새로운 데이터 추가.
	*   @pre   스택은 초기화 되어있다.
	*   @post   If (stack is full), FullStack exception is thrown; otherwise, newItem is at the top of the stack.
	*/
	void Push(T item);

	/**
	*   @brief   스택으로부터 top부분 제거.
	*   @pre   스택은 초기화 되어있다..
	*   @post   If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Pop();

	/**
	*   @brief   스택의 top 데이터를 복사해서 반환.
	*   @pre   스택은 초기화 되어있다.
	*   @post   If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Top();

	/**
	*   @brief   스크린에 스택의 모든 데이터 출력
	*   @pre   스택은 초기화 되어있다.
	*   @post   없음.
	*/
	void Print();
	/**
	*   @brief   대입연산자 오버로딩
	*   @post   입력받은 스택이 딥카피된다.
	*/
	Stack<T>& operator=(const Stack<T>& stack);
private:
	int top;   ///< Number of elements.
	T *items;   ///< Pointer for a stack.
};

//Maxsize로 500까지 할당.
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


// 스택 동적할당 Destruct the object. Free the array dynamically allocated.
template <typename T>
Stack<T>::~Stack()
{
	delete[] items;
}


//스택이 꽉 차있는지 확인.
template <typename T>
bool Stack<T>::IsEmpty() const
{
	if (top <= -1)
		return true;
	else
		return false;
}


//스택이 비어있는지 확인.
template <typename T>
bool Stack<T>::IsFull() const
{
	if (top >= maxStack - 1)
		return true;
	else
		return false;
}

// 스택의 top에 새로운 아이템 추가.
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

// 스택의 top부분 제거
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


// 스택의 top부분 반환
template <typename T>
T Stack<T>::Top()
{
	if (IsEmpty())
		throw EmptyStack();
	else
		return items[top];
}


// 스크린에 스택에 존재하는 데이터 출력
template <typename T>
void Stack<T>::Print()
{
	cout << "Stack: ";
	// Stack 내의 모든 element 출력.
	for (int i = top; i >= 0; i--)
	{
		cout << items[i] << " - ";
	}
	cout << endl;
}

//대입연산자 오버로딩
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