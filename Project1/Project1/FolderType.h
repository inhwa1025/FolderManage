#ifndef _FOLDERTYPE_H
#define _FOLDERTYPE_H
#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <ctime>
#include "DoublyLinkedList.h"
#include "FileType.h"


using namespace std;


/**
*	Relation between two folders.
*/

class FolderType
{
private:
	string fdName;
	string fdPath;
	string fdCreatTime;
	int fdSubFolderNum;
	int fdFileNum;

	DoublySortedLinkedList<FolderType>* fdFolderList; //서브폴더리스트
	DoublySortedLinkedList<FileType>* fdFileList; //서브파일리스트
public:
	/**
	*	default constructor.
	*/
	FolderType()
	{
		fdName = "";
		fdPath = "";
		fdCreatTime = "";
		fdSubFolderNum = 0;
		fdFileNum = 0;
	}

	/**
	*	destructor.
	*/
	~FolderType()
	{
		if (fdSubFolderNum != 0)
			delete fdFolderList;
		if (fdFileNum != 0)
			delete fdFileList;
	}

	/**
	*	@brief	폴더의 이름을 받아온다
	*	@pre	이름이 설정되어있어야함
	*	@post	없음
	*	@return	폴더의 이름 fdName
	*/
	string GetName() { return fdName; }

	/**
	*	@brief	폴더의 위치를 받아온다
	*	@pre	폴더의 위치가 설정되어있어야함
	*	@post	없음
	*	@return	폴더의 위치 fdPath
	*/
	string GetPath() { return fdPath; }

	/**
	*	@brief	폴더의 생성날짜를 받아옴
	*	@pre	없음
	*	@post	폴더의 생성날짜가 설정됨
	*	@return	폴더의 생성날짜 fdCreatTime
	*/
	string GetCreatTime() { return fdCreatTime; }

	/**
	*	@brief	폴더에 포함된 폴더 수를 받아옴
	*	@pre	폴더에 포함된 폴더 수가 설정되어있어야함
	*	@post	없음
	*	@return	폴더에 포함된 폴더 수 fdFolderNum
	*/
	int GetSubFolderNum() { return fdSubFolderNum; }

	/**
	*	@brief	폴더에 포함된 파일 수를 받아옴
	*	@pre	폴더에 포함된 파일 수가 설정되어있어야함
	*	@post	없음
	*	@return	폴더에 포함된 파일 수 fdFileNum
	*/
	int GetFileNum() { return fdFileNum; }

	/**
	*	@brief	폴더의 생성시간을 생성함
	*	@pre	없음
	*	@post	폴더의 생성시간이 생성됨
	*	@return	폴더의 생성시간 curTime
	*/
	string GetCurTime()
	{
		time_t curr_time;
		struct tm *curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);

		string year = to_string(curr_tm->tm_year + 1900) + "년 ";
		string month = to_string(curr_tm->tm_mon + 1) + "월 ";
		string day = to_string(curr_tm->tm_mday) + "일 / ";
		string hour = to_string(curr_tm->tm_hour) + "시 ";
		string minute = to_string(curr_tm->tm_min) + "분 ";
		string second = to_string(curr_tm->tm_sec) + "초 ";
		string curTime = year + month + day + hour + minute + second;

		return curTime;
	}

	/**
	*	@brief	폴더의 이름을 설정.
	*	@pre	없음.
	*	@post	폴더의 이름이 설정된다.
	*	@param	fdName에 넣을 폴더이름을 받아올 파라미터가 name.
	*/
	void SetName(string name) { fdName = name; }

	/**
	*	@brief	폴더의 위치 설정
	*	@pre	없음
	*	@post	폴더의 위치가 설정됨
	*	@param	fdPath에 넣을 위치정보를 받아올 파라미터가 path
	*/
	void SetPath(string path) { fdPath = path; }

	/**
	*	@brief	폴더의 생성시간을 설정
	*	@pre	없음
	*	@post	폴더의 생성시간이 설정됨
	*	@param	fdCreatTime에 넣을 생성시간을 받아올 파라미터가 creatTime
	*/
	void SetCreatTime(string creatTime) { fdCreatTime = creatTime; }

	/**
	*	@brief	폴더에 포함된 서브폴더의 갯수를 설정
	*	@pre	없음
	*	@post	폴더에 포함된 서브폴더의 갯수가 설정됨
	*	@param	fdSubFolderNum에 넣을 위치정보를 받아올 파라미터가 subFolderNum
	*/
	void SetSubFolderNum(int subFolderNum) { fdSubFolderNum = subFolderNum; }

	/**
	*	@brief	폴더에 포함된 파일의 갯수를 설정
	*	@pre	없음
	*	@post	폴더에 포함된 파일의 갯수가 설정됨
	*	@param	fdFileNum에 넣을 위치정보를 받아올 파라미터가 FileNum
	*/
	void SetFileNum(int FileNum) { fdFileNum = FileNum; }

	/**
	*	@brief	화면에 폴더의 속성을 보여줌
	*	@pre	폴더의 속성이 설정되어있어야함
	*	@post	없음
	*/
	void DisplayRecordOnScreen()
	{
		cout << "\t--- 현재 폴더 속성 ---" << endl;
		cout << "\tName   : " << fdName << endl;
		cout << "\tPath   : " << fdPath << endl;
		cout << "\tCreatTime   : " << fdCreatTime << endl;
		cout << "\tSubFolderNum   : " << fdSubFolderNum << endl;
		cout << "\n";
	}

	/**
	*	@brief	키보드로 폴더의 이름을 받아옴
	*	@pre	없음
	*	@post	폴더의 이름을 키보드로 받음
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 폴더의 속성을 받아옴
	*	@pre	없음
	*	@post	폴더의 속성을 키보드로 받음
	*/
	void SetRecordFromKB();

	/**
	*	@brief	두개의 폴더를 이름으로 비교함.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	data	target item for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByID(const FolderType& data);

	/**
	*	@brief	data 폴더에 있는 속성들을 지정한 폴더 속성에 똑같이 입력
	*	@pre	지정할 폴더가 만들어져있어야함
	*	@post	지정한 폴더에 data폴더와 동일한 속성이 설정됨
	*	@param	지정한 폴더에 옮겨넣을 속성을 가진 data폴더
	*	@return	지정한 폴더를 리턴함
	*/
	FolderType& operator= (const FolderType& data);



	// SortedArrayList 관련 함수------------------------------------------

	/**
	*	@brief	새폴더 정보를 키보드로부터 읽어서 폴더리스트에 추가. 처음폴더라면 sortedlist를 동적으로 할당하여 초기화하고 추가
	*	@pre	없음
	*	@post	새폴더가 생성됨
	*/
	int AddFolder();

	/**
	*	@brief	새폴더 정보를 키보드로부터 읽어서 폴더리스트에 추가. 처음폴더라면 sortedlist를 동적으로 할당하여 초기화하고 추가
	*	@pre	없음
	*	@post	새폴더가 생성됨
	*/
	int AddFolder(FolderType* data);

	/**
	*	@brief	삭제할 폴더 정보를 읽어서 해당 폴더를 찾아 삭제
	*	@pre	없음
	*	@post	폴더가 삭제됨
	*/
	int DeleteFolder();

	/**
	*	@brief	삭제할 폴더 정보를 읽어서 해당 폴더를 찾아 삭제
	*	@pre	없음
	*	@post	폴더가 삭제됨
	*/
	int DeleteFolder(FolderType* data);

	/**
	*	@brief	검색할 폴더정보를 화면에서 읽어 검색하여 결과 출력.
	*	@pre	폴더정보가 설정되어있어야함.
	*	@post	없음.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief	현재폴더에 포함된 모든 서브폴더의 이름을 출력
	*	@pre	현재폴더가 설정되어있어야함
	*	@post	없음
	*/
	void DisplayAllFolderName();

	/**
	*	@brief	폴더 이름을 받아 그 폴더를 열어줌.
	*	@pre	폴더가 설정되어있어야함
	*	@post	서브폴더에 들어감과 동시에 그 서브폴더의 주소값을 반환해줌
	*/
	FolderType* OpenSubFolder();


	/**
	*	@brief	'<<' 오버로딩 함수.
	*	@pre	none.
	*	@post	폴더명을 출력
	*/
	friend ostream& operator << (ostream& os, const FolderType& p)
	{
		return os << p.fdName;
	}

	/**
	*	@brief	폴더타입 '==' 오버로딩 함수.
	*	@pre	none.
	*	@post	폴더명이 같으면 true, 다르면 false 리턴.
	*/
	bool operator== (const FolderType& data)
	{
		if (this->fdName == data.fdName)
		{
			return true;
		}
		else
			return false;
	}

	/**
	*	@brief	폴더타입 '>' 오버로딩 함수.
	*	@pre	none.
	*	@post	폴더명이 더 크면 true, 작으면 false 리턴.
	*/
	bool operator> (const FolderType& data)
	{
		if (this->fdName > data.fdName)
		{
			return true;
		}
		else
			return false;
	}

	/**
	*	@brief	폴더타입 '<' 오버로딩 함수.
	*	@pre	none.
	*	@post	폴더명이 더 크면 true, 다르면 false 리턴.
	*/
	bool operator< (const FolderType& data)
	{
		if (this->fdName < data.fdName)
		{
			return true;
		}
		else
			return false;
	}


	/**
	*	@brief	현재폴더에 포함된 모든 파일의 이름을 출력
	*	@pre	현재폴더가 설정되어있어야함
	*	@post	없음
	*/
	void DisplayAllFileName();

	/**
	*	@brief	새파일 정보를 키보드로부터 읽어서 추가.
	*	@pre	없음
	*	@post	새파일이 생성됨
	*/
	int AddFile();

	/**
	*	@brief	새파일 정보를 키보드로부터 읽어서 추가.
	*	@pre	없음
	*	@post	새파일이 생성됨
	*/
	int AddFile(FileType* data);

	/**
	*	@brief	삭제할 파일 정보를 읽어서 해당 파일을 찾아 삭제
	*	@pre	없음
	*	@post	파일이 삭제됨
	*/
	int DeleteFile();

	/**
	*	@brief	삭제할 파일 정보를 읽어서 해당 파일을 찾아 삭제
	*	@pre	없음
	*	@post	파일이 삭제됨
	*/
	int DeleteFile(FileType* data);

	/**
	*	@brief	이름을 받아 그 파일을 열어줌.
	*	@pre	파일이 설정되어있어야함
	*	@post	파일을 열어 파일 내용을 수정할 수 있다
	*/
	FileType* OpenFile();

	/**
	*	@brief	폴더의 이름을 바꿔줌
	*	@pre	변경할 폴더가 존재해야함
	*	@post	폴더 이름이 변경됨
	*/
	int RenameFolder();

	/**
	*	@brief	파일의 이름을 바꿔줌
	*	@pre	변경할 파일이 존재해야함
	*	@post	파일 이름이 변경됨
	*/
	int RenameFile();


};

#endif	// _FOLDERTYPE_H
