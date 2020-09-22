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
	CircularQueueType<FolderType>* m_RecentlyFolder; //최근 열어본 폴더 목록
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
	*	@brief	현재폴더에 있는 서브폴더리스트의 이름을 출력. 서브폴더리스트에 폴더가 1개 이상일때만 실행됨.
	*	@pre	폴더의 서브폴더갯수가 설정되어있어야함
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
	*	@brief	폴더를 삭제한다.
	*	@pre	루트폴더에 폴더가 1개이상이어야한다.
	*	@post	지정한 폴더가 삭제됨.
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
	*	@brief	파일을 삭제한다.
	*	@pre	루트폴더에 파일이 1개이상이어야한다.
	*	@post	지정한 파일이 삭제됨.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteFile();

	/**
	*	@brief	현재 가리키고있는 폴더를 연다.
	*	@pre	폴더의 서브폴더가 설정되어있어야함.
	*	@post	none.
	*/
	void OpenFolder();

	/**
	*	@brief	파일을 연다.
	*	@pre	폴더안에 파일이 생성되어있어야함.
	*	@post	none.
	*/
	void OpenFile();

	/**
	*	@brief	입력한 문자가 포함된 모든 폴더나 파일의 이름을 출력한다.
	*	@pre	루트폴더에 폴더나 파일이 1개 이상이어야한다.
	*	@post	none.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief	최근 열어본 폴더나 파일 10개가 화면에 출력된다.
	*	@pre	최근 열어본 폴더나 파일이 있어야함.
	*	@post	none.
	*/
	void RecentlyFolderList();

	/**
	*	@brief	현재 폴더의 속성 출력
	*	@pre	폴더의 속성이 설정되어있어야함.
	*	@post	none.
	*/
	void DisplayProperty();

	/**
	*	@brief	상위폴더 이동.
	*	@pre	Stack에 경로가 저장되어있어야함.
	*	@post	상위폴더로 이동됨.
	*/
	void MoveParentFolder();

	/**
	*	@brief	폴더 이름 변경
	*	@pre	변경할 폴더가 존재해야함
	*	@post	폴더의 이름이 변경됨
	*/
	void RenameFolder();

	/**
	*	@brief	파일 이름 변경
	*	@pre	변경할 파일이 존재해야함
	*	@post	파일의 이름이 변경됨
	*/
	void RenameFile();

	/**
	*	@brief	폴더 잘라내기
	*	@pre	폴더가 존재해야함
	*	@post	임시저장공간에 폴더가 저장되고 리스트에서 폴더가 빠짐
	*/
	void CutFolder();

	/**
	*	@brief	파일 잘라내기
	*	@pre	파일이 존재해야함
	*	@post	임시저장공간에 파일이 저장되고 리스트에서 파일이 빠짐
	*/
	void CutFile();

	/**
	*	@brief	폴더 복사하기
	*	@pre	폴더가 존재해야함
	*	@post	임시저장공간에 폴더가 저장됨
	*/
	void CopyFolder();

	/**
	*	@brief	파일 복사하기
	*	@pre	파일이 존재해야함
	*	@post	임시저장공간에 파일이 저장됨
	*/
	void CopyFile();

	/**
	*	@brief	폴더 붙여넣기
	*	@pre	없음
	*	@post	name(n)형태로 붙여넣어짐
	*/
	void PasteFolder();

	/**
	*	@brief	파일 붙여넣기
	*	@pre	없음
	*	@post	name(n)형태로 붙여넣어짐
	*/
	void PasteFile();

	/**
	*	@brief	자주사용하는항목 저장
	*	@pre	폴더가 존재해야함
	*	@post	이름을 받아와 그이름과 동일한 폴더가 리스트에 저장됨
	*/
	void BookMark();

	/**
	*	@brief	자주사용하는항목 저장
	*	@pre	폴더가 존재해야함
	*	@post	이름을 받아와 그이름과 동일한 폴더가 리스트에 저장됨
	*/

};

#endif	// _APPLICATION_H