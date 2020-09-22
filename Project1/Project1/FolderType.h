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

	DoublySortedLinkedList<FolderType>* fdFolderList; //������������Ʈ
	DoublySortedLinkedList<FileType>* fdFileList; //�������ϸ���Ʈ
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
	*	@brief	������ �̸��� �޾ƿ´�
	*	@pre	�̸��� �����Ǿ��־����
	*	@post	����
	*	@return	������ �̸� fdName
	*/
	string GetName() { return fdName; }

	/**
	*	@brief	������ ��ġ�� �޾ƿ´�
	*	@pre	������ ��ġ�� �����Ǿ��־����
	*	@post	����
	*	@return	������ ��ġ fdPath
	*/
	string GetPath() { return fdPath; }

	/**
	*	@brief	������ ������¥�� �޾ƿ�
	*	@pre	����
	*	@post	������ ������¥�� ������
	*	@return	������ ������¥ fdCreatTime
	*/
	string GetCreatTime() { return fdCreatTime; }

	/**
	*	@brief	������ ���Ե� ���� ���� �޾ƿ�
	*	@pre	������ ���Ե� ���� ���� �����Ǿ��־����
	*	@post	����
	*	@return	������ ���Ե� ���� �� fdFolderNum
	*/
	int GetSubFolderNum() { return fdSubFolderNum; }

	/**
	*	@brief	������ ���Ե� ���� ���� �޾ƿ�
	*	@pre	������ ���Ե� ���� ���� �����Ǿ��־����
	*	@post	����
	*	@return	������ ���Ե� ���� �� fdFileNum
	*/
	int GetFileNum() { return fdFileNum; }

	/**
	*	@brief	������ �����ð��� ������
	*	@pre	����
	*	@post	������ �����ð��� ������
	*	@return	������ �����ð� curTime
	*/
	string GetCurTime()
	{
		time_t curr_time;
		struct tm *curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);

		string year = to_string(curr_tm->tm_year + 1900) + "�� ";
		string month = to_string(curr_tm->tm_mon + 1) + "�� ";
		string day = to_string(curr_tm->tm_mday) + "�� / ";
		string hour = to_string(curr_tm->tm_hour) + "�� ";
		string minute = to_string(curr_tm->tm_min) + "�� ";
		string second = to_string(curr_tm->tm_sec) + "�� ";
		string curTime = year + month + day + hour + minute + second;

		return curTime;
	}

	/**
	*	@brief	������ �̸��� ����.
	*	@pre	����.
	*	@post	������ �̸��� �����ȴ�.
	*	@param	fdName�� ���� �����̸��� �޾ƿ� �Ķ���Ͱ� name.
	*/
	void SetName(string name) { fdName = name; }

	/**
	*	@brief	������ ��ġ ����
	*	@pre	����
	*	@post	������ ��ġ�� ������
	*	@param	fdPath�� ���� ��ġ������ �޾ƿ� �Ķ���Ͱ� path
	*/
	void SetPath(string path) { fdPath = path; }

	/**
	*	@brief	������ �����ð��� ����
	*	@pre	����
	*	@post	������ �����ð��� ������
	*	@param	fdCreatTime�� ���� �����ð��� �޾ƿ� �Ķ���Ͱ� creatTime
	*/
	void SetCreatTime(string creatTime) { fdCreatTime = creatTime; }

	/**
	*	@brief	������ ���Ե� ���������� ������ ����
	*	@pre	����
	*	@post	������ ���Ե� ���������� ������ ������
	*	@param	fdSubFolderNum�� ���� ��ġ������ �޾ƿ� �Ķ���Ͱ� subFolderNum
	*/
	void SetSubFolderNum(int subFolderNum) { fdSubFolderNum = subFolderNum; }

	/**
	*	@brief	������ ���Ե� ������ ������ ����
	*	@pre	����
	*	@post	������ ���Ե� ������ ������ ������
	*	@param	fdFileNum�� ���� ��ġ������ �޾ƿ� �Ķ���Ͱ� FileNum
	*/
	void SetFileNum(int FileNum) { fdFileNum = FileNum; }

	/**
	*	@brief	ȭ�鿡 ������ �Ӽ��� ������
	*	@pre	������ �Ӽ��� �����Ǿ��־����
	*	@post	����
	*/
	void DisplayRecordOnScreen()
	{
		cout << "\t--- ���� ���� �Ӽ� ---" << endl;
		cout << "\tName   : " << fdName << endl;
		cout << "\tPath   : " << fdPath << endl;
		cout << "\tCreatTime   : " << fdCreatTime << endl;
		cout << "\tSubFolderNum   : " << fdSubFolderNum << endl;
		cout << "\n";
	}

	/**
	*	@brief	Ű����� ������ �̸��� �޾ƿ�
	*	@pre	����
	*	@post	������ �̸��� Ű����� ����
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����� ������ �Ӽ��� �޾ƿ�
	*	@pre	����
	*	@post	������ �Ӽ��� Ű����� ����
	*/
	void SetRecordFromKB();

	/**
	*	@brief	�ΰ��� ������ �̸����� ����.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	data	target item for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByID(const FolderType& data);

	/**
	*	@brief	data ������ �ִ� �Ӽ����� ������ ���� �Ӽ��� �Ȱ��� �Է�
	*	@pre	������ ������ ��������־����
	*	@post	������ ������ data������ ������ �Ӽ��� ������
	*	@param	������ ������ �Űܳ��� �Ӽ��� ���� data����
	*	@return	������ ������ ������
	*/
	FolderType& operator= (const FolderType& data);



	// SortedArrayList ���� �Լ�------------------------------------------

	/**
	*	@brief	������ ������ Ű����κ��� �о ��������Ʈ�� �߰�. ó��������� sortedlist�� �������� �Ҵ��Ͽ� �ʱ�ȭ�ϰ� �߰�
	*	@pre	����
	*	@post	�������� ������
	*/
	int AddFolder();

	/**
	*	@brief	������ ������ Ű����κ��� �о ��������Ʈ�� �߰�. ó��������� sortedlist�� �������� �Ҵ��Ͽ� �ʱ�ȭ�ϰ� �߰�
	*	@pre	����
	*	@post	�������� ������
	*/
	int AddFolder(FolderType* data);

	/**
	*	@brief	������ ���� ������ �о �ش� ������ ã�� ����
	*	@pre	����
	*	@post	������ ������
	*/
	int DeleteFolder();

	/**
	*	@brief	������ ���� ������ �о �ش� ������ ã�� ����
	*	@pre	����
	*	@post	������ ������
	*/
	int DeleteFolder(FolderType* data);

	/**
	*	@brief	�˻��� ���������� ȭ�鿡�� �о� �˻��Ͽ� ��� ���.
	*	@pre	���������� �����Ǿ��־����.
	*	@post	����.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief	���������� ���Ե� ��� ���������� �̸��� ���
	*	@pre	���������� �����Ǿ��־����
	*	@post	����
	*/
	void DisplayAllFolderName();

	/**
	*	@brief	���� �̸��� �޾� �� ������ ������.
	*	@pre	������ �����Ǿ��־����
	*	@post	���������� ���� ���ÿ� �� ���������� �ּҰ��� ��ȯ����
	*/
	FolderType* OpenSubFolder();


	/**
	*	@brief	'<<' �����ε� �Լ�.
	*	@pre	none.
	*	@post	�������� ���
	*/
	friend ostream& operator << (ostream& os, const FolderType& p)
	{
		return os << p.fdName;
	}

	/**
	*	@brief	����Ÿ�� '==' �����ε� �Լ�.
	*	@pre	none.
	*	@post	�������� ������ true, �ٸ��� false ����.
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
	*	@brief	����Ÿ�� '>' �����ε� �Լ�.
	*	@pre	none.
	*	@post	�������� �� ũ�� true, ������ false ����.
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
	*	@brief	����Ÿ�� '<' �����ε� �Լ�.
	*	@pre	none.
	*	@post	�������� �� ũ�� true, �ٸ��� false ����.
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
	*	@brief	���������� ���Ե� ��� ������ �̸��� ���
	*	@pre	���������� �����Ǿ��־����
	*	@post	����
	*/
	void DisplayAllFileName();

	/**
	*	@brief	������ ������ Ű����κ��� �о �߰�.
	*	@pre	����
	*	@post	�������� ������
	*/
	int AddFile();

	/**
	*	@brief	������ ������ Ű����κ��� �о �߰�.
	*	@pre	����
	*	@post	�������� ������
	*/
	int AddFile(FileType* data);

	/**
	*	@brief	������ ���� ������ �о �ش� ������ ã�� ����
	*	@pre	����
	*	@post	������ ������
	*/
	int DeleteFile();

	/**
	*	@brief	������ ���� ������ �о �ش� ������ ã�� ����
	*	@pre	����
	*	@post	������ ������
	*/
	int DeleteFile(FileType* data);

	/**
	*	@brief	�̸��� �޾� �� ������ ������.
	*	@pre	������ �����Ǿ��־����
	*	@post	������ ���� ���� ������ ������ �� �ִ�
	*/
	FileType* OpenFile();

	/**
	*	@brief	������ �̸��� �ٲ���
	*	@pre	������ ������ �����ؾ���
	*	@post	���� �̸��� �����
	*/
	int RenameFolder();

	/**
	*	@brief	������ �̸��� �ٲ���
	*	@pre	������ ������ �����ؾ���
	*	@post	���� �̸��� �����
	*/
	int RenameFile();


};

#endif	// _FOLDERTYPE_H
