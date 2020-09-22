#include "FileType.h"


void FileType::DisplayRecordOnScreen()
{
	cout << "\t--- ���� �Ӽ� ---" << endl;
	cout << "\tName   : " << fName << endl;
	cout << "\tPath   : " << fPath << endl;
	cout << "\tCreatTime    : " << fCreatTime << endl;
	cout << "\tAccessTime   : " << fAccessTime << endl;
	cout << "\t�������α׷� : " << fExtension << endl;
	cout << "\n";
}

void FileType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> fName;
}

void FileType::SetRecordFromKB(string n)
{
	// ���� �̸�
	SetNameFromKB();

	// ���� ���
	SetPath(fPath);

	// ���� ����
	SetCreatTime(GetCurTime());

	SetExtention(n);
}

RelationType FileType::CompareByID(const FileType &data)
{
	if (this->fName > data.fName)
		return GREATER;
	else if (this->fName < data.fName)
		return LESS;
	else
		return EQUAL;
}

FileType& FileType::operator= (const FileType& data)
{
	this->fName = data.fName;
	this->fPath = data.fPath;
	this->fCreatTime = data.fCreatTime;
	this->fAccessTime = data.fAccessTime;
	this->fExtension = data.fExtension;

	return *this;
}

bool FileType::operator== (const FileType& data)
{
	if (this->fName == data.fName)
	{
		return true;
	}
	else
		return false;
}

void ImageType::SetNameFromKB()
{
	string name;
	cout << "\tName : ";
	cin >> name;
	SetName(name + ".jpg");
}

void ImageType::SetRecordFromKB(string n)
{
	// ���� �̸�
	SetNameFromKB();

	// ���� ���
	SetPath(fPath);

	// ���� ����
	SetCreatTime(GetCurTime());

	SetExtention(n);
}

void MusicType::SetNameFromKB()
{
	string name;
	cout << "\tName : ";
	cin >> name;
	SetName(name + ".mp3");
}

void MusicType::SetRecordFromKB(string n)
{
	// ���� �̸�
	SetNameFromKB();

	// ���� ���
	SetPath(fPath);

	// ���� ����
	SetCreatTime(GetCurTime());

	SetExtention(n);
}

void TextType::SetNameFromKB()
{
	string name;
	cout << "\tName : ";
	cin >> name;
	SetName(name + ".txt");
}

void TextType::SetRecordFromKB(string n)
{
	// ���� �̸�
	SetNameFromKB();

	// ���� ���
	SetPath(fPath);

	// ���� ����
	SetCreatTime(GetCurTime());

	SetExtention(n);
}