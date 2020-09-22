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
	cout << "\t---- 즐겨찾기한 폴더 ----" << endl;
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
	cout << "\t---- 최근 열어본 폴더/파일 ----" << endl;

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
	cout << "\t즐겨찾기에 넣고싶은 폴더이름을 입력해주세요." << endl;

	FolderType* temp = m_curFolder->OpenSubFolder();

	m_BookMark->EnQueue(*temp);

}


/*
// Add new record into list.
int Application::AddItem()
{
	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (m_List.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	m_List.Add(item);

	// 현재 list 출력
	DisplayAllItem();

	return 1;
}

//id로 item을 찾아 출력한다.
int Application::SearchItemById()
{
	ItemType item;
	item.SetIdFromKB(); //id입력받는다.

	if (m_List.Get(item)) //0이 아니면(찾으면)
	{
		cout << "<============I FOUND ITEM !==========>" << endl;
		item.DisplayRecordOnScreen(); //해당 item을 출력한다.
		cout << "<====================================>" << endl;
		return 1;	//성공(1)을 리턴
	}
	cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return 0;	//실패(0)을 리턴
}

//이름을 입력받은 item으로 리스트에서 item을 찾아서 출력한다.
int Application::RetriveRecordByMemberName()
{
	ItemType item;
	item.SetNameFromKB(); //name을 입력받는다.

	if (SearchListByMemberName(item)) //0이 아니면(찾으면)
		return 1;	//성공(1)을 리턴
	return 0;	//실패(0)을 리턴
}

//이름으로 item을 찾아서 출력한다.
int Application::SearchListByMemberName(ItemType &inData)
{
	ItemType tmp;
	int result = 0;

	m_List.ResetList();//iterator 초기화
	while (m_List.GetNextItem(tmp) != -1) //리스트의 마지막까지 반복
	{
		if (tmp.GetName().find(inData.GetName()) != -1) //만약 해당 리스트의 이름에 inData의 이름이 존재하면
		{
			if (result == 0) //처음 찾는 경우라면
				cout << "<============I FOUND ITEM !==========>" << endl;
			tmp.DisplayRecordOnScreen();
			result = 1;	//성공(1)
		}
	}
	if (result)	//발견한 경우
		cout << "<====================================>" << endl;
	else	//발견 못하는 경우
		cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return result;
}

//id로 item을 찾아서 제거한다.
int Application::DeleteItem()
{
	int pre = m_List.GetLength();//이전 item개수를 받아온다.
	ItemType item;
	item.SetIdFromKB();

	m_List.Delete(item);

	if (pre > m_List.GetLength()) //이전 item개수보다 현재 item개수가 많아지면 제거성공
	{
		cout << "<========DELETE SUCCESS !===========>" << endl;
		this->DisplayAllItem(); //모든 item을 출력한다.
		return 1;
	}

	cout << "<========DELETE FAIL !=======>" << endl;
	this->DisplayAllItem();//모든 item을 출력한다.
	return 0;
}

//해당 id의 item을 변경한다.
int Application::ReplaceItem()
{
	ItemType item;
	item.SetRecordFromKB(); //키보드로부터 정보를 입력받음

	m_List.Replace(item); //해당 item의 id와 일치하는 것을 찾아 바꾼다.
	this->DisplayAllItem();
	return 0;
}


// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	// list의 모든 데이터를 화면에 출력
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

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_InFile)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_OutFile)	return 0;
	else	return 1;
}


// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!m_InFile.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// 현재 list 출력
	DisplayAllItem();

	return 1;
}


// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	m_List.ResetList();

	// list의 모든 데이터를 파일에 쓰기
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

	item.SetIdFromKB();	//id를 입력받는다
	if (m_List.GetBinarySearch(item))	//이진탐색에 성공했다면
	{
		cout << "<============I FOUND ITEM !==========>" << endl;
		item.DisplayRecordOnScreen();
		cout << "<====================================>" << endl;
		return 1;	//성공(1)을 반환
	}
	//발견 못할시
	cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return 0;	//실패(0)을 반환

}
*/