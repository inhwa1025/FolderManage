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
	string fName; //���� �̸�
	string fPath; //���� ���
	string fCreatTime; //���� ���� ��¥
	string fExtension; //���� Ȯ����
	string fAccessTime; //�������� ��¥
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
	*	@brief	������ �̸��� �޾ƿ´�
	*	@pre	�̸��� �����Ǿ��־����
	*	@post	����
	*	@return	������ �̸� fName
	*/
	string GetName() { return fName; }

	/**
	*	@brief	������ ��ġ�� �޾ƿ´�
	*	@pre	������ ��ġ�� �����Ǿ��־����
	*	@post	����
	*	@return	������ ��ġ fPath
	*/
	string GetPath() { return fPath; }

	/**
	*	@brief	������ ������¥�� �޾ƿ�
	*	@pre	����
	*	@post	������ ������¥�� ������
	*	@return	������ ������¥ fCreatTime
	*/
	string GetCreatTime() { return fCreatTime; }

	/**
	*	@brief	������ �������α׷��� �޾ƿ�
	*	@pre	����
	*	@post	������ �������α׷��� ������
	*	@return	������ �������α׷� fExtension
	*/
	string GetExtension() { return fExtension; }

	/**
	*	@brief	������ �׼�����¥�� �޾ƿ�
	*	@pre	����
	*	@post	������ �׼�����¥�� ������
	*	@return	������ �׼�����¥ fAccessTime
	*/
	string GetAccessTime() { return fAccessTime; }

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
	*	@param	fName�� ���� �����̸��� �޾ƿ� �Ķ���Ͱ� name.
	*/
	void SetName(string name) { fName = name; }

	/**
	*	@brief	������ ��ġ ����
	*	@pre	����
	*	@post	������ ��ġ�� ������
	*	@param	fPath�� ���� ��ġ������ �޾ƿ� �Ķ���Ͱ� path
	*/
	void SetPath(string path) { fPath = path; }

	/**
	*	@brief	������ �����ð��� ����
	*	@pre	����
	*	@post	������ �����ð��� ������
	*	@param	fCreatTime�� ���� �����ð��� �޾ƿ� �Ķ���Ͱ� creatTime
	*/
	void SetCreatTime(string creatTime) { fCreatTime = creatTime; }

	/**
	*	@brief	������ �׼����ð��� ����
	*	@pre	����
	*	@post	������ �׼����ð��� ������
	*	@param	fAccessTime�� ���� �����ð��� �޾ƿ� �Ķ���Ͱ� Time
	*/
	void SetAccessTime(string Time) { fAccessTime = Time; }

	/**
	*	@brief	������ �������α׷� ����
	*	@pre	����
	*	@post	������ �������α׷��� ������
	*	@param	fExtension�� ���� �������α׷� ������ �޾ƿ� �Ķ���Ͱ� extension
	*/
	void SetExtention(string extension) { fExtension = extension; }

	/**
	*	@brief	ȭ�鿡 ������ �Ӽ��� ������
	*	@pre	������ �Ӽ��� �����Ǿ��־����
	*	@post	����
	*/
	void DisplayRecordOnScreen();

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
	void SetRecordFromKB(string n);

	/**
	*	@brief	�ΰ��� ������ �̸����� ����.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	data	target item for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByID(const FileType& data);

	/**
	*	@brief	data ���Ͽ� �ִ� �Ӽ����� ������ ���� �Ӽ��� �Ȱ��� �Է�
	*	@pre	������ ������ ��������־����
	*	@post	������ ���Ͽ� data���Ͽ� ������ �Ӽ��� ������
	*	@param	������ ���Ͽ� �Űܳ��� �Ӽ��� ���� data����
	*	@return	������ ���ϸ� ������
	*/
	FileType& operator= (const FileType& data);

	/**
	*	@brief	'<<' �����ε� �Լ�.
	*	@pre	none.
	*	@post	���ϸ��� ���
	*/
	friend ostream& operator << (ostream& os, const FileType& p)
	{
		return os << p.fName;
	}

	/**
	*	@brief	����Ÿ�� '==' �����ε� �Լ�.
	*	@pre	none.
	*	@post	���ϸ��� ������ true, �ٸ��� false ����.
	*/
	bool operator== (const FileType& data);

	/**
	*	@brief	����Ÿ�� '>' �����ε� �Լ�.
	*	@pre	none.
	*	@post	���ϸ��� �� ũ�� true, ������ false ����.
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
	*	@brief	����Ÿ�� '<' �����ε� �Լ�.
	*	@pre	none.
	*	@post	���ϸ��� �� ũ�� false, ������ true ����.
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
	*	@brief	���ϸ� ����
	*	@pre	none.
	*	@post	���ϸ� ����
	*/
	void SetName(string n)
	{
		fName = n;
	}

	/**
	*	@brief	�������α׷� ����
	*	@pre	none.
	*	@post	�������α׷� ����
	*/
	void SetExtention(string n)
	{
		fExtension = n;
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
	void SetRecordFromKB(string n);
};

class MusicType : public FileType
{
public:
	MusicType() : FileType() {}

	/**
	*	@brief	���ϸ� ����
	*	@pre	none.
	*	@post	���ϸ� ����
	*/
	void SetName(string n)
	{
		fName = n;
	}

	/**
	*	@brief	�������α׷� ����
	*	@pre	none.
	*	@post	�������α׷� ����
	*/
	void SetExtention(string n)
	{
		fExtension = n;
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
	void SetRecordFromKB(string n);

};

class TextType : public FileType
{
public:
	TextType() : FileType() {}


	/**
	*	@brief	���ϸ� ����
	*	@pre	none.
	*	@post	���ϸ� ����
	*/
	void SetName(string n)
	{
		fName = n;
	}

	/**
	*	@brief	�������α׷� ����
	*	@pre	none.
	*	@post	�������α׷� ����
	*/
	void SetExtention(string n)
	{
		fExtension = n;
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
	void SetRecordFromKB(string n);

};
