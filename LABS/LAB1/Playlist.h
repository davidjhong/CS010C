#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>

using namespace std;

class PlaylistNode {
private:
    // private data members
    string uniqueID; // private members are initialized in the default constructor to "none" and 0
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;

public: 
    // Default constructor, takes no parameters
    PlaylistNode();
    
    // Parameterized constructor; id, name, artist, length
    PlaylistNode(string id, string name, string artist, int length);

    // Inserts new node after the current node
    void InsertAfter(PlaylistNode* node);

    // Sets the next node pointer (mutator function)
    void SetNext(PlaylistNode* nextNode);

    // Accessor functions - CONST
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;

    // Prints the information of a specific node in the list
    void PrintPlaylistNode();
};

// Class for PrintMenu functions (options)
class Playlist {
    private:     
        string title;
        PlaylistNode* head;
        PlaylistNode* tail;
    public:
        // Default Constructor
        Playlist();

        //Parameterized Constructor
        Playlist(string title);

        // Destructor
        ~Playlist();

        // Copy assignment and copy constructor
        Playlist(const Playlist &cpy);
        Playlist & operator=(const Playlist &rhs);

        // Options from printmenu
        void OutputFullPlaylist();
        void AddSong();
        void RemoveSong();
        void ChangePosition();
        void OutPutSongsByArtist();
        void OutputTotalSongTime();
    
};

#endif
