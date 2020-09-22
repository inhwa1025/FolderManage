#include "Application.h"


// Program driver.
void Application::Run()
{
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:
			NewFolder();
			break;
		case 2:
			DeleteFolder();
			break;
		case 3:
			NewFile();
			break;
		case 4:
			DeleteFile();
			break;
		case 5:
			OpenFolder();
			break;
		case 6:
			OpenFile();
			break;
		case 7:
			RetrieveFolderByName();
			break;
		case 8:
			RecentlyFolderList();
			break;
		case 9:
			DisplayProperty();
			break;
		case 10:
			MoveParentFolder();
			break;
		case 11:
			RenameFolder();
			break;
		case 12:
			RenameFile();
			break;
		case 13:
			CutFolder();
			break;
		case 14:
			CutFile();
			break;
		case 15:
			CopyFolder();
			break;
		case 16:
			CopyFile();
			break;
		case 17:
			PasteFolder();
			break;
		case 18:
			PasteFile();
			break;
		case 19:
			BookMark();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;

	cout << "\t" << m_curFolder->GetPath() << endl;
	DisplayCurFolderList();
	cout << "\t---- ���ã���� ���� ----" << endl;
	m_BookMark->Print();

	cout << "\t---- Menu ---- " << endl;
	cout << "\t    1 : Create New Folder" << endl;
	cout << "\t    2 : Delete Folder" << endl;
	cout << "\t    3 : Create New File" << endl;
	cout << "\t    4 : Delete File" << endl;
	cout << "\t    5 : Open Folder" << endl;
	cout << "\t    6 : Open File" << endl;
	cout << "\t    7 : Retrieve Folder/File" << endl;
	cout << "\t    8 : Recently Folder/File List" << endl;
	cout << "\t    9 : Display Property Current Folder" << endl;
	cout << "\t   10 : Move To Parent Folder" << endl;
	cout << "\t   11 : Rename Folder" << endl;
	cout << "\t   12 : Rename File" << endl;
	cout << "\t   13 : Cut Folder" << endl;
	cout << "\t   14 : Cut File" << endl;
	cout << "\t   15 : Copy Folder" << endl;
	cout << "\t   16 : Copy File" << endl;
	cout << "\t   17 : Paste Folder" << endl;
	cout << "\t   18 : Paste File" << endl;
	cout << "\t   19 : Folder BookMark" << endl;
	//cout << "\t   20 : " << endl;
	cout << "\t    0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

void Application::DisplayCurFolderList()
{
	m_curFolder->DisplayAllFolderName();
	m_curFolder->DisplayAllFileName();
}


int Application::NewFolder()
{
	return m_curFolder->AddFolder();
}


int Application::DeleteFolder()
{
	return m_curFolder->DeleteFolder();
}


void Application::NewFile()
{
	m_curFolder->AddFile();
}


int Application::DeleteFile()
{
	return m_curFolder->DeleteFile();
}


void Application::OpenFolder()
{
	FolderType* temp = m_curFolder->OpenSubFolder();

	m_curFolder = temp;
	m_Folder->Push(m_curFolder);
	m_RecentlyFolder->EnQueue(*m_curFolder);
}

void Application::OpenFile()
{
	FileType* temp = m_curFolder->OpenFile();
	if (temp != NULL)
	{
		m_RecentlyFile->EnQueue(*temp);
	}
}


int Application::RetrieveFolderByName()
{
	return m_curFolder->RetrieveFolderByName();
}


void Application::RecentlyFolderList()
{
	cout << "\t---- �ֱ� ��� ����/���� ----" << endl;

	m_RecentlyFolder->Print();
}


void Application::DisplayProperty()
{
	m_curFolder->DisplayRecordOnScreen();
}


void Application::MoveParentFolder()
{
	m_Folder->Pop();
	m_curFolder = m_Folder->Top();
}


void Application::RenameFolder()
{
	m_curFolder->RenameFolder();
}


void Application::RenameFile()
{
	m_curFolder->RenameFile();
}

void Application::CutFolder()
{
	if (m_curFolder->GetSubFolderNum() == 0)
		cout << "\tError" << endl;
	else
	{
		FolderType* data;
		data = new FolderType;
		data = m_curFolder->OpenSubFolder();
		m_fdClipBoard = data;
		m_fClipBoard_Parent = m_curFolder;
		state = 1;
	}
}

void Application::CutFile()
{
	if (m_curFolder->GetFileNum() == 0)
		cout << "\tError" << endl;
	else
	{
		FileType* data;
		data = new FileType;
		data = m_curFolder->OpenFile();
		m_fClipBoard = data;
		m_fClipBoard_Parent = m_curFolder;
		state = 1;
	}
}

void Application::CopyFolder()
{
	if (m_curFolder->GetSubFolderNum() == 0)
		cout << "\tError" << endl;
	else
	{
		FolderType* data;
		data = new FolderType;
		data = m_curFolder->OpenSubFolder();
		m_fdClipBoard = data;
		m_fClipBoard_Parent = m_curFolder;
		state = 2;
		pasteNum = 0;
	}
}

void Application::CopyFile()
{
	if (m_curFolder->GetFileNum() == 0)
		cout << "\tError" << endl;
	else
	{
		FileType* data;
		data = new FileType;
		data = m_curFolder->OpenFile();
		m_fClipBoard = data;
		m_fClipBoard_Parent = m_curFolder;
		state = 2;
		pasteNum = 0;
	}
}

void Application::PasteFolder()
{
	if (m_fdClipBoard != nullptr)
	{
		if (state == 1)
		{
			if (m_curFolder != m_fClipBoard_Parent)
			{
				m_curFolder->AddFolder(m_fdClipBoard);
				m_fClipBoard_Parent->DeleteFolder(m_fdClipBoard);
				m_fdClipBoard = nullptr;
			}
		}
		else if (state == 2)
		{
			FolderType temp;
			pasteNum++;
			temp = *m_fdClipBoard;
			temp.SetName(temp.GetName() + "(" + to_string(pasteNum) + ")");
			temp.SetPath(m_curFolder->GetPath() + "/" + temp.GetName());
			m_curFolder->AddFolder(&temp);
		}
	}
	else
		cout << "\tError" << endl;
}

void Application::PasteFile()
{
	if (state == 1)
	{
		if (m_curFolder != m_fClipBoard_Parent)
		{
			m_curFolder->AddFile(m_fClipBoard);
			m_fClipBoard_Parent->DeleteFile(m_fClipBoard);
			m_fClipBoard = nullptr;
		}
	}
	else if (state == 2)
	{
		FileType temp;
		pasteNum++;
		temp = *m_fClipBoard;
		temp.SetName(temp.GetName() + "(" + to_string(pasteNum) + ")");
		temp.SetPath(m_curFolder->GetPath() + "/" + temp.GetName());
		m_curFolder->AddFile(&temp);
	}
	else
		cout << "\tError" << endl;
}

void Application::BookMark()
{
	cout << "\t���ã�⿡ �ְ���� �����̸��� �Է����ּ���." << endl;

	FolderType* temp = m_curFolder->OpenSubFolder();

	m_BookMark->EnQueue(*temp);

}


/*
// Add new record into list.
int Application::AddItem()
{
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if (m_List.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	m_List.Add(item);

	// ���� list ���
	DisplayAllItem();

	return 1;
}

//id�� item�� ã�� ����Ѵ�.
int Application::SearchItemById()
{
	ItemType item;
	item.SetIdFromKB(); //id�Է¹޴´�.

	if (m_List.Get(item)) //0�� �ƴϸ�(ã����)
	{
		cout << "<============I FOUND ITEM !==========>" << endl;
		item.DisplayRecordOnScreen(); //�ش� item�� ����Ѵ�.
		cout << "<====================================>" << endl;
		return 1;	//����(1)�� ����
	}
	cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return 0;	//����(0)�� ����
}

//�̸��� �Է¹��� item���� ����Ʈ���� item�� ã�Ƽ� ����Ѵ�.
int Application::RetriveRecordByMemberName()
{
	ItemType item;
	item.SetNameFromKB(); //name�� �Է¹޴´�.

	if (SearchListByMemberName(item)) //0�� �ƴϸ�(ã����)
		return 1;	//����(1)�� ����
	return 0;	//����(0)�� ����
}

//�̸����� item�� ã�Ƽ� ����Ѵ�.
int Application::SearchListByMemberName(ItemType &inData)
{
	ItemType tmp;
	int result = 0;

	m_List.ResetList();//iterator �ʱ�ȭ
	while (m_List.GetNextItem(tmp) != -1) //����Ʈ�� ���������� �ݺ�
	{
		if (tmp.GetName().find(inData.GetName()) != -1) //���� �ش� ����Ʈ�� �̸��� inData�� �̸��� �����ϸ�
		{
			if (result == 0) //ó�� ã�� �����
				cout << "<============I FOUND ITEM !==========>" << endl;
			tmp.DisplayRecordOnScreen();
			result = 1;	//����(1)
		}
	}
	if (result)	//�߰��� ���
		cout << "<====================================>" << endl;
	else	//�߰� ���ϴ� ���
		cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return result;
}

//id�� item�� ã�Ƽ� �����Ѵ�.
int Application::DeleteItem()
{
	int pre = m_List.GetLength();//���� item������ �޾ƿ´�.
	ItemType item;
	item.SetIdFromKB();

	m_List.Delete(item);

	if (pre > m_List.GetLength()) //���� item�������� ���� item������ �������� ���ż���
	{
		cout << "<========DELETE SUCCESS !===========>" << endl;
		this->DisplayAllItem(); //��� item�� ����Ѵ�.
		return 1;
	}

	cout << "<========DELETE FAIL !=======>" << endl;
	this->DisplayAllItem();//��� item�� ����Ѵ�.
	return 0;
}

//�ش� id�� item�� �����Ѵ�.
int Application::ReplaceItem()
{
	ItemType item;
	item.SetRecordFromKB(); //Ű����κ��� ������ �Է¹���

	m_List.Replace(item); //�ش� item�� id�� ��ġ�ϴ� ���� ã�� �ٲ۴�.
	this->DisplayAllItem();
	return 0;
}


// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	// list�� ��� �����͸� ȭ�鿡 ���
	m_List.ResetList();
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.DisplayRecordOnScreen();
		curIndex = m_List.GetNextItem(data);
	}
}


// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	m_InFile.open(fileName);	// file open for reading.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_InFile)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!m_OutFile)	return 0;
	else	return 1;
}


// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// �б�� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while (!m_InFile.eof())
	{
		// array�� �л����� ������ ����ִ� structure ����
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// ���� list ���
	DisplayAllItem();

	return 1;
}


// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	m_List.ResetList();

	// list�� ��� �����͸� ���Ͽ� ����
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = m_List.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}

int Application::SearchItemByBinarySearch()
{
	ItemType item;

	item.SetIdFromKB();	//id�� �Է¹޴´�
	if (m_List.GetBinarySearch(item))	//����Ž���� �����ߴٸ�
	{
		cout << "<============I FOUND ITEM !==========>" << endl;
		item.DisplayRecordOnScreen();
		cout << "<====================================>" << endl;
		return 1;	//����(1)�� ��ȯ
	}
	//�߰� ���ҽ�
	cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return 0;	//����(0)�� ��ȯ

}
*/