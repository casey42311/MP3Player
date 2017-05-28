#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include "Song.h"
using namespace std;

char Song::currentMP3_[ENTRY_SZ] = " ";
char Song::songListFile_[ENTRY_SZ] = " ";

Song::Song()
{

}

Song::Song(string name)
{
	string song;
	reverse(name.begin(), name.end());
	unsigned pos = name.find("\\");
	song = name.substr(0, pos);
	reverse(song.begin(), song.end());

	strcpy_s(songName_, song.c_str());
}

void Song::SetSongPath(string path)
{
	strcpy_s(songPath_, path.c_str());
}

const char* Song::GetSongName()
{
	return songName_;
}

void Song::AppendToListFile()
{
	ofstream out;

	out.open(songListFile_, ofstream::app); //Open and move to the end of the output file

	out << songPath_ << endl;
	
	out.close();
	out.clear(std::ios_base::goodbit);
}

void Song::PlaySong()
{
    const int BUFF_SZ = 512;
    char fullStr[BUFF_SZ];
    MCIERROR err;

    StopSong();

    // Set global variable so we know this file is playing.
    // Sandwich the file path in escaped double quotes so
    // spaces can be included and don't need to double up
    // on the backslashes.
    sprintf_s(currentMP3_, ENTRY_SZ, "\"%s\"", songPath_);
    sprintf_s(fullStr, BUFF_SZ,
        "open %s type mpegvideo alias myFile", currentMP3_);
    err = mciSendString(fullStr, NULL, 0, 0); 
    if (err != 0)
    {
        cout << "command: " << fullStr << endl;
        mciGetErrorString(err, fullStr, BUFF_SZ);
        cout << err << ": " << fullStr << endl << endl;
    }
    else
    {
        err = mciSendString("play myFile", NULL, 0, 0);
    }
}

void Song::StopSong()
{
    MCIERROR err;

    // Stop any currently playing file
    if (currentMP3_[0] != 0)
    {
        err = mciSendString("stop myFile", NULL, 0, 0);
        err = mciSendString("close myFile", NULL, 0, 0);
        currentMP3_[0] = 0;
    }
}

Song::~Song()
{

}
