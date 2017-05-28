/***********************************************************************************************
Name: Casey Benson
Date: 02/19/2014
Assignment: 4
Description: LLQueue_MP3Player
************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "Song.h"
#include "LinkedList.h"
using namespace std;

LinkedList LL;

char DisplayMenu();
void LoadSongFile();
void AddNewSong();
void DeleteSong();
void PlaySong();
void PrintAllSongs();

void main()
{
    char selection = ' ';

    while (selection != 'f')
    {
        selection = tolower(DisplayMenu());

        switch(selection)
        {
        case 'a':
            LoadSongFile();
            break;
        case 'b':
            AddNewSong();
            break;
        case 'c':
            DeleteSong();
            break;
        case 'd':
            PlaySong();
            break;
        case 'e':
			PrintAllSongs();
            break;
		case 'f':
			return;
        default:
            cout << "That is not a valid choice!\n";
        }
    }
}

char DisplayMenu()
{
	char selection = ' ';
	cout << "a) Open a song file"
		 << "\nb) Add a song"
		 << "\nc) Delete a song"
		 << "\nd) Play a song"
		 << "\ne) Print all songs"
		 << "\nf) Quit" << endl;
	cin >> selection;
	cout << endl;
	return selection;
}

void LoadSongFile()
{
	string songListFile, filepath;
	ifstream inFile;
	int count = 0;

	cout << "Enter the full file path to the song file: ";
	cin >> songListFile;

	inFile.open(songListFile);

	if (!inFile)
	{
		cout << "\nFile not found." << endl;
		return;
	}

	while (!inFile.eof())
	{
		strcpy_s(Song::songListFile_, songListFile.c_str());
		strcpy_s(Song::currentMP3_, songListFile.c_str());

		getline(inFile, filepath);
		if(filepath == "")
		{
			break;
		}
		Song* songPtr = new Song(filepath);
		songPtr->SetSongPath(filepath);

		LL.AddLinkToBack(songPtr);

		count++;
	}

	inFile.close();
	inFile.clear(std::ios_base::goodbit);

	cout << "\nLoaded the file and read " << count << " song objects." << endl << endl;
}

void AddNewSong()
{
	if(LL.GetListLength() == 0)
	{
		cout << "A file must be loaded first." << endl << endl;
		return;
	}
	string filepath;
	cin.ignore(INT_MAX,'\n');

	cout << "\nEnter the full song path and name: ";
	getline(cin, filepath);

	Song* songPtr = new Song(filepath);
	songPtr->SetSongPath(filepath);

	LL.AddLinkToBack(songPtr);
	
	songPtr->AppendToListFile();

	cout << endl;
}

void DeleteSong()
{
	if(LL.GetListLength() == 0)
	{
		cout << "A file must be loaded first." << endl << endl;
		return;
	}
	Node* tempNode = LL.GetFirstNode();
	Song* delSong = ((Song*)tempNode->data_);
	string removeSong;
	cin.ignore(INT_MAX,'\n');

	cout << "Enter the song name with extension: ";
	getline(cin, removeSong);

	while(delSong->GetSongName() != removeSong)
	{
		tempNode = tempNode->next_;
		if(tempNode == nullptr)
		{
			cout << "Could not find that song in the list!" << endl << endl;
			return;
		}
		delSong = ((Song*)tempNode->data_);
	}
	
	LL.RemoveThisLink(tempNode);
	delete delSong;
	delete tempNode;

	cout << endl;
}

void PlaySong()
{
	if(LL.GetListLength() == 0)
	{
		cout << "A file must be loaded first." << endl << endl;
		return;
	}
	Node* tempNode = LL.GetFirstNode();
	Song* playSong = ((Song*)tempNode->data_);
	string song;
	cin.ignore(INT_MAX,'\n');

	cout << "Enter the song name with extension: ";
	getline(cin, song);

	while(playSong->GetSongName() != song)
	{
		tempNode = tempNode->next_;
		if(tempNode == nullptr)
		{
			cout << "Could not find that song in the list!" << endl;
			return;
		}
		playSong = ((Song*)tempNode->data_);
	}
	playSong->PlaySong();

	cout << endl;
}

void PrintAllSongs()
{
	Node* printNode = LL.GetFirstNode();
	if(printNode == nullptr) //Returns an error message if there is nothing to print
	{
		cout << "Nothing to print." << endl << endl;
		return;
	}
	if(LL.GetListLength() == 1)
	{
		cout << ((Song*)printNode->data_)->GetSongName();
		return;
	}
	while(printNode != nullptr) //While not at the end of the list
	{
		cout << ((Song*)printNode->data_)->GetSongName() << endl;
		printNode = printNode->next_;
	}

	cout << endl;
}