#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H


#include "FolderType.h"
#include "FileType.h"
#include "Queue.h"
#include "Stack.h"


/**
*	application class for item management simply.
*/
class Application
{
private:
	FolderType m_RootFolder;		///< item list.criptor.
	FolderType *m_curFolder;		///< item list.
	FolderType *m_fdClipBoard;
	FileType *m_fClipBoard;
	FolderType *m_fClipBoard_Parent;
	int state;
	int pasteNum;
	int m_Command;			///< current command number.
	CircularQueueType<FolderType>* m_RecentlyFolder; //�ֱ� ��� ���� ���
	CircularQueueType<FileType>* m_RecentlyFile;
	Stack<FolderType*> *m_Folder;
	CircularQueueType<FolderType>* m_BookMark;


public:
	/**
	*	default constructor.
	*/
	Application()
	{
		m_Command = 0;

		m_RootFolder.SetName("root");
		m_RootFolder.SetPath("/root");
		m_RootFolder.SetCreatTime(m_RootFolder.GetCurTime());
		m_RootFolder.SetSubFolderNum(0);
		m_RootFolder.SetFileNum(0);

		m_Folder = new Stack<FolderType*>;
		m_RecentlyFolder = new CircularQueueType<FolderType>;
		m_RecentlyFile = new CircularQueueType<FileType>;
		m_fdClipBoard = nullptr;
		m_fClipBoard = nullptr;
		m_fClipBoard_Parent = nullptr;
		state = 0;
		pasteNum = 0;

		m_curFolder = &m_RootFolder;

		m_Folder->Push(&m_RootFolder);

		m_BookMark = new CircularQueueType<FolderType>;
	}

	/**
	*	destructor.
	*/
	~Application()
	{
		delete m_Folder;
		delete m_RecentlyFolder;
	}


	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	���������� �ִ� ������������Ʈ�� �̸��� ���. ������������Ʈ�� ������ 1�� �̻��϶��� �����.
	*	@pre	������ �������������� �����Ǿ��־����
	*	@post	none.
	*/
	void DisplayCurFolderList();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int NewFolder();

	/**
	*	@brief	������ �����Ѵ�.
	*	@pre	��Ʈ������ ������ 1���̻��̾���Ѵ�.
	*	@post	������ ������ ������.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteFolder();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void NewFile();

	/**
	*	@brief	������ �����Ѵ�.
	*	@pre	��Ʈ������ ������ 1���̻��̾���Ѵ�.
	*	@post	������ ������ ������.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteFile();

	/**
	*	@brief	���� ����Ű���ִ� ������ ����.
	*	@pre	������ ���������� �����Ǿ��־����.
	*	@post	none.
	*/
	void OpenFolder();

	/**
	*	@brief	������ ����.
	*	@pre	�����ȿ� ������ �����Ǿ��־����.
	*	@post	none.
	*/
	void OpenFile();

	/**
	*	@brief	�Է��� ���ڰ� ���Ե� ��� ������ ������ �̸��� ����Ѵ�.
	*	@pre	��Ʈ������ ������ ������ 1�� �̻��̾���Ѵ�.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief	�ֱ� ��� ������ ���� 10���� ȭ�鿡 ��µȴ�.
	*	@pre	�ֱ� ��� ������ ������ �־����.
	*	@post	none.
	*/
	void RecentlyFolderList();

	/**
	*	@brief	���� ������ �Ӽ� ���
	*	@pre	������ �Ӽ��� �����Ǿ��־����.
	*	@post	none.
	*/
	void DisplayProperty();

	/**
	*	@brief	�������� �̵�.
	*	@pre	Stack�� ��ΰ� ����Ǿ��־����.
	*	@post	���������� �̵���.
	*/
	void MoveParentFolder();

	/**
	*	@brief	���� �̸� ����
	*	@pre	������ ������ �����ؾ���
	*	@post	������ �̸��� �����
	*/
	void RenameFolder();

	/**
	*	@brief	���� �̸� ����
	*	@pre	������ ������ �����ؾ���
	*	@post	������ �̸��� �����
	*/
	void RenameFile();

	/**
	*	@brief	���� �߶󳻱�
	*	@pre	������ �����ؾ���
	*	@post	�ӽ���������� ������ ����ǰ� ����Ʈ���� ������ ����
	*/
	void CutFolder();

	/**
	*	@brief	���� �߶󳻱�
	*	@pre	������ �����ؾ���
	*	@post	�ӽ���������� ������ ����ǰ� ����Ʈ���� ������ ����
	*/
	void CutFile();

	/**
	*	@brief	���� �����ϱ�
	*	@pre	������ �����ؾ���
	*	@post	�ӽ���������� ������ �����
	*/
	void CopyFolder();

	/**
	*	@brief	���� �����ϱ�
	*	@pre	������ �����ؾ���
	*	@post	�ӽ���������� ������ �����
	*/
	void CopyFile();

	/**
	*	@brief	���� �ٿ��ֱ�
	*	@pre	����
	*	@post	name(n)���·� �ٿ��־���
	*/
	void PasteFolder();

	/**
	*	@brief	���� �ٿ��ֱ�
	*	@pre	����
	*	@post	name(n)���·� �ٿ��־���
	*/
	void PasteFile();

	/**
	*	@brief	���ֻ���ϴ��׸� ����
	*	@pre	������ �����ؾ���
	*	@post	�̸��� �޾ƿ� ���̸��� ������ ������ ����Ʈ�� �����
	*/
	void BookMark();

	/**
	*	@brief	���ֻ���ϴ��׸� ����
	*	@pre	������ �����ؾ���
	*	@post	�̸��� �޾ƿ� ���̸��� ������ ������ ����Ʈ�� �����
	*/

};

#endif	// _APPLICATION_H