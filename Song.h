#include <string>
using namespace std;
const int ENTRY_SZ = 512;

class Song
{
private:
    char songPath_[ENTRY_SZ];   // Contains the full path name
    char songName_[ENTRY_SZ];   // Song name extracted from the path

public:

    // Store the path name of the song list file
    static char songListFile_[ENTRY_SZ];
    static char currentMP3_[ENTRY_SZ];

    // Static method to empty the song list file
    static void ClearListFile();

    Song();
    Song(string name);
    ~Song();
    void SetSongPath(string path);
    const char* GetSongName();
    void AppendToListFile();
    void PlaySong();
    void StopSong();
};
