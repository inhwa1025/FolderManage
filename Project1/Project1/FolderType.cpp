#include "FolderType.h"
#include "DoublyLinkedList.h"
#include "DoublyIterator.h"

void FolderType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> fdName;
}


void FolderType::SetRecordFromKB()
{
	// 폴더 이름
	SetNameFromKB();

	// 폴더 경로
	SetPath(fdPath + "/" + fdName);

	// 폴더 생성
	SetCreatTime(GetCurTime());

	// 서브 폴더 수
	SetSubFolderNum(0);
}


RelationType FolderType::CompareByID(const FolderType &data)
{
	if (this->fdName > data.fdName)
		return GREATER;
	else if (this->fdName < data.fdName)
		return LESS;
	else
		return EQUAL;
}


int FolderType::AddFolder()
{
	if (fdSubFolderNum == 0)
		fdFolderList = new DoublySortedLinkedList<FolderType>;
	FolderType data;
	while (1)
	{
		data.SetPath(fdPath);
		data.SetRecordFromKB();
		if (fdFolderList->Get(data))
		{
			cout << "\t일치하는 이름의 폴더가 존재합니다. 다시 설정해주세요." << endl;
		}
		else
			break;
	}


	if (fdFolderList->Add(data))
		fdSubFolderNum++;

	return 1;
}

int FolderType::AddFolder(FolderType* data)
{
	if (fdSubFolderNum == 0)
		fdFolderList = new DoublySortedLinkedList<FolderType>;
	data->SetPath(fdPath + "/" + data->GetName());
	fdFolderList->Add(*data);
	fdSubFolderNum++;

	return 1;

}


int FolderType::DeleteFolder()
{
	if (fdSubFolderNum != 0)
	{
		FolderType data;

		data.SetNameFromKB();
		if (fdFolderList->Delete(data))
		{
			cout << "\t삭제를 완료했습니다." << endl;
			fdSubFolderNum--;
		}
		else
			cout << "\t삭제하지 못했습니다. 일치하는 항목을 찾을 수 없습니다." << endl;
	}

	return 1;
}

int FolderType::DeleteFolder(FolderType* data)
{
	fdFolderList->Delete(*data);
	fdSubFolderNum--;

	return 1;
}


int FolderType::RetrieveFolderByName()
{
	if ((fdSubFolderNum == 0) & (fdFileNum == 0))
		return 0;
	else
	{
		FolderType data;
		data.SetNameFromKB();

		FolderType temp;
		FileType temp1;

		cout << "\n\t-Search result-" << endl;

		cout << "\t-Folder-" << endl;
		// list의 모든 데이터를 화면에 출력
		DoublyIterator<FolderType> itor(*fdFolderList);
		for (int i = 0; i < fdFolderList->GetLength(); i++)
		{
			temp = itor.Next();
			if (temp.GetName().find(data.GetName()) != string::npos)
				temp.DisplayRecordOnScreen();
		}

		cout << "\t-File-" << endl;
		DoublyIterator<FileType> itor2(*fdFileList);
		for (int i = 0; i < fdFileList->GetLength(); i++)
		{
			temp1 = itor2.Next();
			if (temp1.GetName().find(data.GetName()) != string::npos)
				temp1.DisplayRecordOnScreen();
		}

		return 1;
	}

}


void FolderType::DisplayAllFolderName()
{
	cout << "\tCurrent Path : " << GetPath() << endl;

	if (fdSubFolderNum != 0)
	{
		FolderType data;

		cout << "\n\t--Current folder list--" << endl;

		// list의 모든 데이터를 화면에 출력
		DoublyIterator<FolderType> itor(*fdFolderList);
		for (int i = 0; i < fdFolderList->GetLength(); i++)
		{
			data = itor.Next();
			cout << "\t" << data.GetName() << endl;
		}
	}
	else
		cout << "\t--- No Folders ---" << endl;
}

FolderType* FolderType::OpenSubFolder()
{
	if (fdSubFolderNum == 0)
		return this;
	FolderType data;
	data.SetNameFromKB();

	DoublyIterator<FolderType> itor(*fdFolderList);
	if (fdFolderList->Get(data))
	{
		return fdFolderList->GetCurNode(data);
		/*while (itor.GetCurrentNode() == data)
		{
			itor.Next();
		}
		return &(itor.GetCurrentNode());*/
	}
	else
	{
		cout << "\t 일치하는 하위폴더가 없습니다!" << endl;
		return this;
	}
}



FolderType& FolderType::operator= (const FolderType& data)
{
	this->fdName = data.fdName;
	this->fdPath = data.fdPath;
	this->fdCreatTime = data.fdCreatTime;
	this->fdSubFolderNum = data.fdSubFolderNum;

	if (fdSubFolderNum != 0)
	{
		this->fdFolderList = data.fdFolderList;
	}

	return *this;
}


void FolderType::DisplayAllFileName()
{

	if (fdFileNum != 0)
	{
		FileType data;

		cout << "\n\t--Current file list--" << endl;

		// list의 모든 데이터를 화면에 출력
		DoublyIterator<FileType> itor(*fdFileList);
		for (int i = 0; i < fdFileList->GetLength(); i++)
		{
			data = itor.Next();
			cout << "\t" << data.GetName() << endl;
		}
	}
	else
		cout << "\t--- No Files ---" << endl;
}

int FolderType::AddFile()
{
	if (fdFileNum == 0)
		fdFileList = new DoublySortedLinkedList<FileType>;

	int command;
	cout << "\t---파일 형식 선택---" << endl;
	cout << "\t1. Image (.jpg)" << endl;
	cout << "\t2. Music (.mp3)" << endl;
	cout << "\t3. Memo  (.txt)" << endl;
	cout << "\t";
	cin >> command;

	FileType file;
	while (1)
	{
		switch (command)
		{
		case 1:
			file.SetRecordFromKB("Image Program");
			file.SetExtention("Image Program");
			file.SetName(file.GetName() + ".jpg");
			break;
		case 2:
			file.SetRecordFromKB("Music Player");
			file.SetExtention("Music Player");
			file.SetName(file.GetName() + ".mp3");
			break;
		case 3:
			file.SetRecordFromKB("Memo Pad");
			file.SetExtention("Memo Pad");
			file.SetName(file.GetName() + ".txt");
			break;
		default:
			cout << "Error : 잘못된 입력" << endl;
			return 0;
			break;
		}
		file.SetPath(fdPath);
		file.SetCreatTime(GetCurTime());
		if (fdFileList->Add(file))
		{
			fdFileNum++;
			return 1;
			break;
		}
		else
			cout << "\t일치하는 이름의 파일이 존재합니다. 다시 설정해주세요." << endl;
	}
	

	/*if (command == 1)
	{
		ImageType image;

		while (1)
		{
			string n = "Image Program";
			image.SetRecordFromKB(n);
			image.SetExtention(n);
			image.SetPath(fdPath);
			image.SetCreatTime(GetCurTime());

			if (fdFileList->Add(image))
			{
				fdFileNum++;
				break;
			}
			else
				cout << "\t일치하는 이름의 파일이 존재합니다. 다시 설정해주세요." << endl;
		}


		return 1;
	}
	else if (command == 2)
	{
		MusicType music;

		while (1)
		{
			string n = "Music Player";
			music.SetRecordFromKB(n);
			music.SetExtention(n);
			music.SetPath(fdPath);
			music.SetCreatTime(GetCurTime());

			if (fdFileList->Add(music))
			{
				fdFileNum++;
				break;
			}
			else
				cout << "\t일치하는 이름의 파일이 존재합니다. 다시 설정해주세요." << endl;
		}

		return 1;
	}
	else if (command == 3)
	{
		TextType txt;

		while (1)
		{
			string n = "Memo Pad";
			txt.SetRecordFromKB(n);
			txt.SetExtention(n);
			txt.SetPath(fdPath);
			txt.SetCreatTime(GetCurTime());

			if (fdFileList->Add(txt))
			{
				fdFileNum++;
				ofstream txt(txt.GetName());
				txt.close();
				break;
			}
			else
				cout << "\t일치하는 이름의 파일이 존재합니다. 다시 설정해주세요." << endl;
		}
		return 1;
	}
	else
	{
		cout << "Error : 잘못된 입력" << endl;
		return 0;
	}*/
}

int FolderType::AddFile(FileType* data)
{
	if (fdFileNum == 0)
		fdFileList = new DoublySortedLinkedList<FileType>;
	data->SetPath(fdPath);
	fdFileList->Add(*data);
	fdFileNum++;

	return 1;
}

int FolderType::DeleteFile()
{
	if (fdFileNum != 0)
	{
		FileType data;

		data.SetNameFromKB();
		if (fdFileList->Delete(data))
		{
			cout << "\t삭제를 완료했습니다." << endl;
			fdFileNum--;
		}
		else
			cout << "\t삭제하지 못했습니다. 일치하는 항목을 찾을 수 없습니다." << endl;

	}

	return 1;
}

int FolderType::DeleteFile(FileType* data)
{
	fdFileList->Delete(*data);
	fdFileNum--;

	return 1;
}

FileType* FolderType::OpenFile()
{
	if (fdFileNum == 0) {
		return NULL;
		cout << "\t 파일이 없습니다!" << endl;
	}
	else
	{
		FileType data;
		data.SetNameFromKB();
		DoublyIterator<FileType> itor(*fdFileList);
		if (fdFileList->Get(data))
		{
			/*FileType* temp = fdFileList->GetCurNode(data);
			return temp;
			temp->SetAccessTime(GetCurTime());
			temp->DisplayRecordOnScreen();*/
			fdFileList->GetCurNode(data)->SetAccessTime(GetCurTime());
			fdFileList->GetCurNode(data)->DisplayRecordOnScreen();
			return fdFileList->GetCurNode(data);
		}
		else
		{
			cout << "\t 일치하는 파일이 없습니다!" << endl;
			return NULL;
		}

		
	}
}

int FolderType::RenameFolder()
{
	FolderType* data = OpenSubFolder();
	if (data->GetPath() != "")
	{
		string preName = data->GetName();

		cout << "\t변경할 이름을 입력하세요." << endl;
		data->SetNameFromKB();

		if (fdFolderList->Get(*data))
		{
			data->SetPath(fdPath + "/" + data->GetName());
			fdFolderList->Replace(*data); //리스트 재정렬
			return 1;
		}
		else
		{
			data->SetName(preName);
			cout << "\t오류! 변경하려는 폴더의 이름이 이미 있습니다!" << endl;
			return 0;
		}
	}
	else
	{
		cout << "\t폴더를 찾을 수 없습니다." << endl;
		return 0;
	}

}

int FolderType::RenameFile()
{
	FileType* data = OpenFile();
	if (data->GetPath() != "")
	{
		string preName = data->GetName();

		cout << "\t변경할 이름을 입력하세요." << endl;
		data->SetNameFromKB();
		if (fdFileList->Get(*data))
		{
			fdFileList->Replace(*data);
			data = nullptr;
			return 1;
		}
		else
		{
			data->SetName(preName);
			cout << "\t오류! 변경하려는 폴더의 이름이 이미 있습니다!" << endl;
			return 0;
		}
	}
	else
	{
		cout << "\t폴더를 찾을 수 없습니다." << endl;
		return 0;
	}

	return 0;
}

