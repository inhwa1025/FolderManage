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
	*	@brief	Primary key(�й�)�� �������� �˻��Ͽ� �ش��ϴ� ������ ������.
	*	@pre	����Ʈ�� ����/�ʱ�ȭ �Ϸ�Ǿ��ִ� ���¿��� ��.
	*	@post	��ġ�ϴ� �����Ͱ� ����Ʈ�� ���� ��� ������.
	*	@param	data	primary key�� �ݵ�� ���ԵǾ� �ִ� ��ü.
	*	@return ������ ��ġ�ϴ� �����Ͱ� ������ ���� �� 1, ������ 0�� ����.
	*/
	int Delete(T data);

	/**
	*	@brief	Primary key(�й�)�� �������� �˻��Ͽ� �ش��ϴ� ������ ���� ä������.
	*	@pre	����Ʈ�� ����/�ʱ�ȭ �Ϸ�Ǿ��ִ� ���¿��� ��.
	*	@post	��ġ�ϴ� �����Ͱ� ����Ʈ�� ���� ��� ���ο� �����ͷ� ��ü��.
	*	@param	data	primary key�� �ݵ�� ���ԵǾ� �ִ� ��ü.
	*/
	void Replace(T data);

	/**
	*	@brief	�̸��� ��ġ�ϴ� �����͸� ã����
	*	@pre	����Ʈ�� ����/�ʱ�ȭ �Ϸ�Ǿ��ִ� ���¿��� ��.
	*	@post	��ġ�ϴ� �����Ͱ� ����Ʈ�� ���� ��� �� ������ �ּҰ� ��ȯ
	*	@param	data	primary key�� �ݵ�� ���ԵǾ� �ִ� ��ü.
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

	m_nLength = 0; // ���̴� 0.
}


// Class destructor
template <typename T>
DoublySortedLinkedList<T>::~DoublySortedLinkedList()
{
	//����Ʈ���� ��� node ����
	MakeEmpty();
}

// Determines whether the list is full.
// �ִ� ���� 20���� ��������
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
	itor.Next(); // �������� �̵�.

	while (itor.NextNotNull())
	{
		pItem = itor.m_pCurPointer;
		itor.Next(); // ���� �����͸� �������� �̵�.
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
	if (IsEmpty()) // ó�� ������ ��
	{
		DoublyNodeType<T> *pItem = new DoublyNodeType<T>;

		//m_pFirst�� pItem����
		m_pFirst->next = pItem;
		pItem->prev = m_pFirst;

		//m_pLast�� pItem����
		m_pLast->prev = pItem;
		pItem->next = m_pLast;

		pItem->data = item;

		m_nLength++;
		return 1;
	}
	else // ó���� �ƴ� ��
	{
		DoublyIterator<T> itor(*this);
		itor.Next(); // �������� �̵�.
		while (1)
		{
			if (itor.m_pCurPointer->next == nullptr) // ����Ʈ�� �������϶�
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // �������� ����.
				m_nLength++;
				return 1;
				break;
			}
			else if (item < itor.m_pCurPointer->data)// �´� �ڸ��� ã�´�.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // �������� ����.
				m_nLength++;
				return 1;
				break;
			}
			else
				itor.Next(); // �������� �̵�.
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
		int count = 0;	// �� ��°�� ��ġ�ϰ� �ִ��� ���� (������ 0)
					// iterator�� ����ϸ鼭 curPointer�� ������ �� �����Ƿ� return value�� �ǹ̸� ����
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



// Ư�� ��Ҹ� ã�� �����ϴ� �Լ�
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

// �������Ѵ�.
template <typename T>
void DoublySortedLinkedList<T>::Replace(T data) {

	DoublyIterator<T> itor(*this);
	DoublyIterator<T> itor2(*this);
	itor.Next(); // �������� �̵�.
	itor2.Next(); // �������� �̵�.

	while (itor.m_pCurPointer != m_pLast)
	{
		if (itor.m_pCurPointer->data == data)
			break;
		else
			itor.Next();
	}

	//�������ϱ�
	itor.m_pCurPointer->next->prev = itor.m_pCurPointer->prev;
	itor.m_pCurPointer->prev->next = itor.m_pCurPointer->next;

	while (1)
	{
		if (itor2.m_pCurPointer->next == nullptr)
		{
			itor.m_pCurPointer->prev = itor2.m_pCurPointer->prev;
			itor.m_pCurPointer->next = itor2.m_pCurPointer;
			itor2.m_pCurPointer->prev->next = itor.m_pCurPointer;
			itor2.m_pCurPointer->prev = itor.m_pCurPointer; // �������� ����.
			break;
		}
		else if (itor.m_pCurPointer->data < itor2.m_pCurPointer->data) // �´� �ڸ��� ã�´�.
		{
			itor.m_pCurPointer->prev = itor2.m_pCurPointer->prev;
			itor.m_pCurPointer->next = itor2.m_pCurPointer;
			itor2.m_pCurPointer->prev->next = itor.m_pCurPointer;
			itor2.m_pCurPointer->prev = itor.m_pCurPointer; // �������� ����.
			break;
		}
		else
			itor2.Next(); // �������� �̵�.
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