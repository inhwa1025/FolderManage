#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "DoublyLinkedList.h"

using namespace std;

class FileType
{
protected:
	string fName; //파일 이름
	string fPath; //저장 경로
	string fCreatTime; //파일 생성 날짜
	string fExtension; //파일 확장자
	string fAccessTime; //엑세스한 날짜
public:
	/**
	*	default constructor.
	*/
	FileType()
	{
		fName = "";
		fPath = "";
		fCreatTime = "";
		fExtension = "";
		fAccessTime = "";
	}
	/**
	*	destructor.
	*/
	~FileType()
	{

	}

	/**
	*	@brief	파일의 이름을 받아온다
	*	@pre	이름이 설정되어있어야함
	*	@post	없음
	*	@return	파일의 이름 fName
	*/
	string GetName() { return fName; }

	/**
	*	@brief	파일의 위치를 받아온다
	*	@pre	파일의 위치가 설정되어있어야함
	*	@post	없음
	*	@return	파일의 위치 fPath
	*/
	string GetPath() { return fPath; }

	/**
	*	@brief	파일의 생성날짜를 받아옴
	*	@pre	없음
	*	@post	파일의 생성날짜가 설정됨
	*	@return	파일의 생성날짜 fCreatTime
	*/
	string GetCreatTime() { return fCreatTime; }

	/**
	*	@brief	파일의 연결프로그램을 받아옴
	*	@pre	없음
	*	@post	파일의 연결프로그램이 설정됨
	*	@return	파일의 연결프로그램 fExtension
	*/
	string GetExtension() { return fExtension; }

	/**
	*	@brief	파일의 액세스날짜를 받아옴
	*	@pre	없음
	*	@post	파일의 액세스날짜가 설정됨
	*	@return	파일의 액세스날짜 fAccessTime
	*/
	string GetAccessTime() { return fAccessTime; }

	/**
	*	@brief	파일의 생성시간을 생성함
	*	@pre	없음
	*	@post	파일의 생성시간이 생성됨
	*	@return	파일의 생성시간 curTime
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
	*	@brief	파일의 이름을 설정.
	*	@pre	없음.
	*	@post	파일의 이름이 설정된다.
	*	@param	fName에 넣을 파일이름을 받아올 파라미터가 name.
	*/
	void SetName(string name) { fName = name; }

	/**
	*	@brief	파일의 위치 설정
	*	@pre	없음
	*	@post	파일의 위치가 설정됨
	*	@param	fPath에 넣을 위치정보를 받아올 파라미터가 path
	*/
	void SetPath(string path) { fPath = path; }

	/**
	*	@brief	파일의 생성시간을 설정
	*	@pre	없음
	*	@post	파일의 생성시간이 설정됨
	*	@param	fCreatTime에 넣을 생성시간을 받아올 파라미터가 creatTime
	*/
	void SetCreatTime(string creatTime) { fCreatTime = creatTime; }

	/**
	*	@brief	파일의 액세스시간을 설정
	*	@pre	없음
	*	@post	파일의 액세스시간이 설정됨
	*	@param	fAccessTime에 넣을 생성시간을 받아올 파라미터가 Time
	*/
	void SetAccessTime(string Time) { fAccessTime = Time; }

	/**
	*	@brief	파일의 연결프로그램 설정
	*	@pre	없음
	*	@post	파일의 연결프로그램이 설정됨
	*	@param	fExtension에 넣을 연결프로그램 정보를 받아올 파라미터가 extension
	*/
	void SetExtention(string extension) { fExtension = extension; }

	/**
	*	@brief	화면에 파일의 속성을 보여줌
	*	@pre	파일의 속성이 설정되어있어야함
	*	@post	없음
	*/
	void DisplayRecordOnScreen();

	/**
	*	@brief	키보드로 파일의 이름을 받아옴
	*	@pre	없음
	*	@post	파일의 이름을 키보드로 받음
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 파일의 속성을 받아옴
	*	@pre	없음
	*	@post	파일의 속성을 키보드로 받음
	*/
	void SetRecordFromKB(string n);

	/**
	*	@brief	두개의 파일을 이름으로 비교함.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	data	target item for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByID(const FileType& data);

	/**
	*	@brief	data 파일에 있는 속성들을 지정한 파일 속성에 똑같이 입력
	*	@pre	지정할 파일이 만들어져있어야함
	*	@post	지정한 파일에 data파일와 동일한 속성이 설정됨
	*	@param	지정한 파일에 옮겨넣을 속성을 가진 data파일
	*	@return	지정한 파일를 리턴함
	*/
	FileType& operator= (const FileType& data);

	/**
	*	@brief	'<<' 오버로딩 함수.
	*	@pre	none.
	*	@post	파일명을 출력
	*/
	friend ostream& operator << (ostream& os, const FileType& p)
	{
		return os << p.fName;
	}

	/**
	*	@brief	파일타입 '==' 오버로딩 함수.
	*	@pre	none.
	*	@post	파일명이 같으면 true, 다르면 false 리턴.
	*/
	bool operator== (const FileType& data);

	/**
	*	@brief	파일타입 '>' 오버로딩 함수.
	*	@pre	none.
	*	@post	파일명이 더 크면 true, 작으면 false 리턴.
	*/
	bool operator> (const FileType& data)
	{
		if (this->fName > data.fName)
		{
			return true;
		}
		else
			return false;
	}

	/**
	*	@brief	파일타입 '<' 오버로딩 함수.
	*	@pre	none.
	*	@post	파일명이 더 크면 false, 작으면 true 리턴.
	*/
	bool operator< (const FileType& data)
	{
		if (this->fName < data.fName)
		{
			return true;
		}
		else
			return false;
	}
};

class ImageType : public FileType
{
public:
	ImageType() : FileType() {}


	/**
	*	@brief	파일명 설정
	*	@pre	none.
	*	@post	파일명 변경
	*/
	void SetName(string n)
	{
		fName = n;
	}

	/**
	*	@brief	연결프로그램 설정
	*	@pre	none.
	*	@post	연결프로그램 변경
	*/
	void SetExtention(string n)
	{
		fExtension = n;
	}

	/**
	*	@brief	키보드로 파일의 이름을 받아옴
	*	@pre	없음
	*	@post	파일의 이름을 키보드로 받음
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 파일의 속성을 받아옴
	*	@pre	없음
	*	@post	파일의 속성을 키보드로 받음
	*/
	void SetRecordFromKB(string n);
};

class MusicType : public FileType
{
public:
	MusicType() : FileType() {}

	/**
	*	@brief	파일명 설정
	*	@pre	none.
	*	@post	파일명 변경
	*/
	void SetName(string n)
	{
		fName = n;
	}

	/**
	*	@brief	연결프로그램 설정
	*	@pre	none.
	*	@post	연결프로그램 변경
	*/
	void SetExtention(string n)
	{
		fExtension = n;
	}

	/**
	*	@brief	키보드로 파일의 이름을 받아옴
	*	@pre	없음
	*	@post	파일의 이름을 키보드로 받음
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 파일의 속성을 받아옴
	*	@pre	없음
	*	@post	파일의 속성을 키보드로 받음
	*/
	void SetRecordFromKB(string n);

};

class TextType : public FileType
{
public:
	TextType() : FileType() {}


	/**
	*	@brief	파일명 설정
	*	@pre	none.
	*	@post	파일명 변경
	*/
	void SetName(string n)
	{
		fName = n;
	}

	/**
	*	@brief	연결프로그램 설정
	*	@pre	none.
	*	@post	연결프로그램 변경
	*/
	void SetExtention(string n)
	{
		fExtension = n;
	}

	/**
	*	@brief	키보드로 파일의 이름을 받아옴
	*	@pre	없음
	*	@post	파일의 이름을 키보드로 받음
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 파일의 속성을 받아옴
	*	@pre	없음
	*	@post	파일의 속성을 키보드로 받음
	*/
	void SetRecordFromKB(string n);

};
