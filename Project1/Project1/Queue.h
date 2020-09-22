#pragma once
#include "folderType.h"
#include <iostream>
using namespace std;

#define maxQueue 10


/**
*	@brief	Exception class thrown by Enqueue when queue is full.
*/
class FullQueue
{
public:
	/**
	*	@brief	Display a message for full queue on screen.
	*/
	void print()
	{
		cout << "\tFullQueue exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Dequeue when queue is empty.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	Display a message for empty queue on screen.
	*/
	void print()
	{
		cout << "\tEmtpyQueue exception thrown." << endl;
	}
};

/**
*	@brief	Queue class.
*	@details	This class processes as First In, First Out (FIFO), 템플릿을 적용해 다양한 변수 타입을 저장할 수 있다.
*/
template <typename T>
class CircularQueueType
{
public:
	/**
	*	@brief	Allocate dynamic array whose size is maxQueue.
	*	@pre	The maxQueue is defined
	*	@post	Member of items points the allocated array.
	*/
	CircularQueueType();

	/**
	*	@brief	Allocate dynamic array whose size is max.
	*	@pre	none.
	*	@post	Member of items points the allocated array.
	*/
	CircularQueueType(int max);

	/**
	*	@brief	Destruct the object. Free the array dynamically allocated.
	*	@pre	Release memory for queue pointer.
	*	@post	none.
	*/
	~CircularQueueType();


	/**
	*	@brief	Determines whether the queue is full.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is full)
	*/
	bool IsFull();

	/**
	*	@brief	Determines whether the queue is empty.
	*	@pre	Queue has been initialized.
	*	@post	Function value = (queue is empty)
	*/
	bool IsEmpty();

	/**
	*	@brief	Makes the queue empty.
	*	@pre	Queue has been initialized.
	*	@post	m_iFront와 m_iRear is set same value as Constructer.
	*/
	void MakeEmpty();

	/**
	*	@brief	Adds newItem to the last of the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is full), FullQueue exception is thrown; otherwise, newItem is at the last.
	*/
	void EnQueue(T item);

	/**
	*	@brief	Removes first item from the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (queue is empty), EmptyQueue exception is thrown; otherwise, first element has been removed from queue. item gets value of removed item.
	*/
	void DeQueue(T &item);

	/**
	*	@brief	Print all the items in the queue on screen
	*	@pre	Queue has been initialized.
	*	@post	None.
	*/
	void Print();

	/**
	*	@brief	찾고자 하는 폴더가 현재 큐에 있는지 확인.
	*	@pre	None.
	*	@post	None.
	*/
	int Check(T newitem, int x);

private:
	int m_iFront;	//index of one infront of the first element.
	int m_iRear;	//index of the last element.
	int m_nMaxQueue;	//max size of the queue.
	T* m_pItems;	//pointer for dynamic allocation.
};

//Allocate dynamic array whose size is maxQueue.
template <typename T>
CircularQueueType<T>::CircularQueueType()
{
	m_pItems = new T[maxQueue];	//m_pItems에 크기가 maxQueue인 배열을 만든다.
	m_nMaxQueue = maxQueue;
	m_iFront = m_nMaxQueue - 1;
	m_iRear = m_nMaxQueue - 1;	//멤버 변수들을 초기화시켜준다.
}

//Allocate dynamic array whose size is max.
template <typename T>
CircularQueueType<T>::CircularQueueType(int max)
{
	m_pItems = new T[max];	//m_pItems에 크기가 max인 배열을 만든다.
	m_nMaxQueue = max;
	m_iFront = m_nMaxQueue - 1;
	m_iRear = m_nMaxQueue - 1;	//멤버 변수들을 초기화시켜준다.
}

//Destruct the object. Free the array dynamically allocated.
template <typename T>
CircularQueueType<T>::~CircularQueueType()
{
	delete[] m_pItems;	//동적할당했던 메모리를 해제해준다.
}

//Determines whether the queue is full.
template <typename T>
bool CircularQueueType<T>::IsFull()
{
	if (m_iFront - m_iRear == 1 || m_iRear - m_iFront == m_nMaxQueue - 1)
		return 1;	//m_iFront가 m_iRear보다 1 앞일때는 꽉 찬것이므로 1을 리턴한다. m_iFront가 0일때는 m_iRear가 m_nMaxQueue-1과 같을때 꽉 찬것이다.
	return 0;	//꽉 차지 않았으면 0을 리턴한다.
}

//Determines whether the queue is empty.
template <typename T>
bool CircularQueueType<T>::IsEmpty()
{
	if (m_iFront == m_iRear)
		return 1;	//m_iFront와 m_iRear가 같은 경우는 queue가 비어있는 상태이므로 1을 리턴한다.
	return 0;	//비어있지 않으면 0을 리턴한다.
}

//Makes the queue empty.
template <typename T>
void CircularQueueType<T>::MakeEmpty()
{
	m_iFront = m_nMaxQueue - 1;
	m_iRear = m_nMaxQueue - 1;	//생성자와 같은 값으로 m_iFront와 m_iRear를 변경해준다.
}

//Adds newItem to the last of the queue.
template <typename T>
void CircularQueueType<T>::EnQueue(T item)
{
	int temp = 0;


	if (Check(item, temp) != 0)
	{
		for (int i = temp; i < m_iRear; i++)
		{
			m_pItems[i] = m_pItems[i + 1];
		}
		m_pItems[m_iRear] = item;
	}
	else
	{
		m_iRear = (m_iRear + 1) % m_nMaxQueue;
		m_pItems[m_iRear] = item;
	}
}

//Removes first item from the queue.
template <typename T>
void CircularQueueType<T>::DeQueue(T& item)
{
	if (IsEmpty())
		throw EmptyQueue();	//비어있을땐 throw EmptyQueue
	else
	{
		m_iFront = (m_iFront + 1) % m_nMaxQueue;
		item = m_pItems[m_iFront];	//m_iFront를 1 증가시켜주고 삭제될 값을 item에 복사해준다.
	}

}

//Print all the items in the queue on screen
template <typename T>
void CircularQueueType<T>::Print()
{
	if (IsEmpty())				//비었으면 it is empty출력. Empty Stack을 throw하면 프로그램이 종료되어서 다시 Enqueue할수없으므로
		cout << "\t" << endl;				//부득이하게 새로운 예외처리
	else
	{
		// CircularQueueType 내의모든element 출력.
		int first = m_iFront;
		int last = m_iRear;
		while (first != last)				//Rear값과 front가 같지 않을동안만. front로 시작해서 값을 하나씩 출력.Enqueue하면 rear가 front에 비해 앞서있으므로
		{
			cout << "\t" << m_pItems[(first + 1) % m_nMaxQueue] << endl;
			first = (first + 1) % m_nMaxQueue;
		}
		cout << endl;
	}
}


template <typename T>
int CircularQueueType<T>::Check(T newItem, int x)
{
	for (int i = 0; i < m_nMaxQueue; i++)
	{
		if (m_pItems[i] == newItem)
		{
			x = i;
		}
	}
	return x;

}