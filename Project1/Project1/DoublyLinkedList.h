#pragma once

#ifndef _SORTED_LINKED_LIST_H
#define _SORTED_LINKED_LIST_H

#include "DoublyIterator.h"

enum RelationType { LESS, GREATER, EQUAL };

/**
*	Structure for NodeType to use in Linked structure.
*/

template <typename T>
class DoublyIterator;

template <typename T>
struct DoublyNodeType
{
	T data;	///< A data for each node.
	DoublyNodeType* prev;	///< A node pointer of previous node.
	DoublyNodeType* next;	///< A node pointer of next node.
};


/**
*	Single sorted list class for managing items.
*/
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>;
public:
	/**
	*	default constructor.
	*/
	DoublySortedLinkedList();

	/**
	*	destructor.
	*/
	~DoublySortedLinkedList();

	/**
	*	@brief	Determines whether the list is full.
	*	@pre	List has been initialized.
	*	@post	None.
	*	@return	If there is not memory left, throws bad_alloc exception and return true, otherwise false.
	*/
	bool IsFull();

	/**
	*	@brief	Determines whether the list is empty.
	*	@pre	List has been initialized.
	*	@post	None.
	*	@return	Return true if the list is empty, otherwise false.
	*/
	bool IsEmpty();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);

	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);

	/**
	*	@brief	Primary key(학번)를 바탕으로 검색하여 해당하는 정보를 삭제함.
	*	@pre	리스트가 존재/초기화 완료되어있는 상태여야 함.
	*	@post	일치하는 데이터가 리스트에 있을 경우 삭제됨.
	*	@param	data	primary key가 반드시 포함되어 있는 객체.
	*	@return 삭제할 일치하는 데이터가 있으면 삭제 후 1, 없으면 0을 리턴.
	*/
	int Delete(T data);

	/**
	*	@brief	Primary key(학번)를 바탕으로 검색하여 해당하는 정보를 새로 채워넣음.
	*	@pre	리스트가 존재/초기화 완료되어있는 상태여야 함.
	*	@post	일치하는 데이터가 리스트에 있을 경우 새로운 데이터로 교체됨.
	*	@param	data	primary key가 반드시 포함되어 있는 객체.
	*/
	void Replace(T data);

	/**
	*	@brief	이름이 일치하는 데이터를 찾아줌
	*	@pre	리스트가 존재/초기화 완료되어있는 상태여야 함.
	*	@post	일치하는 데이터가 리스트에 있을 경우 그 데이터 주소값 반환
	*	@param	data	primary key가 반드시 포함되어 있는 객체.
	*/
	T* GetCurNode(T data);

private:
	DoublyNodeType<T>* m_pFirst;	///< Pointer for pointing a first node.
	DoublyNodeType<T>* m_pLast; ///< Last node.
	int m_nLength;	///< Number of node in the list.
};


// Class constructor
template <typename T>
DoublySortedLinkedList<T>::DoublySortedLinkedList()
{
	m_pFirst = new DoublyNodeType<T>;
	m_pLast = new DoublyNodeType<T>;

	m_pFirst->prev = nullptr;
	m_pFirst->next = m_pLast;
	m_pLast->next = nullptr;
	m_pLast->prev = m_pFirst;

	m_nLength = 0; // 길이는 0.
}


// Class destructor
template <typename T>
DoublySortedLinkedList<T>::~DoublySortedLinkedList()
{
	//리스트내의 모든 node 제거
	MakeEmpty();
}

// Determines whether the list is full.
// 최대 갯수 20개로 임의지정
template <typename T>
bool DoublySortedLinkedList<T>::IsFull() {
	if (m_nLength == 20)
		return true;
	else
		return false;
}

// Determines whether the list is empty.
template <typename T>
bool DoublySortedLinkedList<T>::IsEmpty() {
	if (m_nLength == 0) {
		return true;
	}
	else
		return false;
}

// Initialize list to empty state.
template <typename T>
void DoublySortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	DoublyNodeType<T> *pItem;
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	while (itor.NextNotNull())
	{
		pItem = itor.m_pCurPointer;
		itor.Next(); // 현재 포인터를 다음으로 이동.
		delete pItem;
	}

	m_pFirst->prev = nullptr;
	m_pFirst->next = m_pLast;
	m_pLast->next = nullptr;
	m_pLast->prev = m_pFirst;
	m_nLength = 0;
}


// Get number of elements in the list.
template <typename T>
int DoublySortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}


// Add item into this list.
template <typename T>
int DoublySortedLinkedList<T>::Add(T item)
{
	if (IsEmpty()) // 처음 삽입할 때
	{
		DoublyNodeType<T> *pItem = new DoublyNodeType<T>;

		//m_pFirst와 pItem연결
		m_pFirst->next = pItem;
		pItem->prev = m_pFirst;

		//m_pLast과 pItem연결
		m_pLast->prev = pItem;
		pItem->next = m_pLast;

		pItem->data = item;

		m_nLength++;
		return 1;
	}
	else // 처음이 아닐 때
	{
		DoublyIterator<T> itor(*this);
		itor.Next(); // 다음으로 이동.
		while (1)
		{
			if (itor.m_pCurPointer->next == nullptr) // 리스트의 마지막일때
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // 아이템을 삽입.
				m_nLength++;
				return 1;
				break;
			}
			else if (item < itor.m_pCurPointer->data)// 맞는 자리를 찾는다.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // 아이템을 삽입.
				m_nLength++;
				return 1;
				break;
			}
			else
				itor.Next(); // 다음으로 이동.
		}
	}
}


// Retrieve list element whose key matches item's key (if present).
template <typename T>
int DoublySortedLinkedList<T>::Get(T& item)
{
	if (m_nLength == 0)
		return 0;
	else
	{
		DoublyIterator<T> iter(*this);
		int count = 0;	// 몇 번째에 위치하고 있는지 리턴 (없으면 0)
					// iterator를 사용하면서 curPointer를 재사용할 수 없으므로 return value의 의미를 변경
		bool found = false;
		while (iter.NotNull()) {
			count++;
			if (item == iter.GetCurrentNode()) {
				found = true;
				item = iter.GetCurrentNode();
				break;
			}
			else if (item < iter.GetCurrentNode()) {
				break;
			}
			else {
				iter.Next();
			}
		}

		if (found) {
			return count;
		}
		else return 0;
	}


}



// 특정 요소를 찾아 삭제하는 함수
template <typename T>
int DoublySortedLinkedList<T>::Delete(T data) {
	DoublyNodeType<T>* pNode = m_pFirst;
	int positionIndex = Get(data);
	if (positionIndex) {
		for (int i = 1; i < positionIndex; i++) {
			pNode = pNode->next;
		}

		pNode->next->prev = pNode->prev;
		pNode->prev->next = pNode->next;

		delete pNode;
		m_nLength--;
		return 1;
	}
	else return 0;

}

// 재정렬한다.
template <typename T>
void DoublySortedLinkedList<T>::Replace(T data) {

	DoublyIterator<T> itor(*this);
	DoublyIterator<T> itor2(*this);
	itor.Next(); // 다음으로 이동.
	itor2.Next(); // 다음으로 이동.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == data)
			break;
		else
			itor.Next();
	}

	//재정렬하기
	itor.m_pCurPointer->next->prev = itor.m_pCurPointer->prev;
	itor.m_pCurPointer->prev->next = itor.m_pCurPointer->next;

	while (1)
	{
		if (itor2.m_pCurPointer->next == nullptr)
		{
			itor.m_pCurPointer->prev = itor2.m_pCurPointer->prev;
			itor.m_pCurPointer->next = itor2.m_pCurPointer;
			itor2.m_pCurPointer->prev->next = itor.m_pCurPointer;
			itor2.m_pCurPointer->prev = itor.m_pCurPointer; // 아이템을 삽입.
			break;
		}
		else if (itor.m_pCurPointer->data < itor2.m_pCurPointer->data) // 맞는 자리를 찾는다.
		{
			itor.m_pCurPointer->prev = itor2.m_pCurPointer->prev;
			itor.m_pCurPointer->next = itor2.m_pCurPointer;
			itor2.m_pCurPointer->prev->next = itor.m_pCurPointer;
			itor2.m_pCurPointer->prev = itor.m_pCurPointer; // 아이템을 삽입.
			break;
		}
		else
			itor2.Next(); // 다음으로 이동.
	}

}

template <typename T>
T* DoublySortedLinkedList<T>::GetCurNode(T data)
{
	DoublyNodeType<T>* pNode = m_pFirst;
	int positionIndex = Get(data);
	if (positionIndex) {
		for (int i = 1; i < positionIndex; i++) {
			pNode = pNode->next;
		}
	}
	return &pNode->data;
}



#endif	// LINKED_LIST