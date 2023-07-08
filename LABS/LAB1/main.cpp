#include <iostream>
#include <string>
// Include cstdlib for exit(1)
#include <cstdlib>
#include "Playlist.h"

using namespace std;

// Declare the printmenu function before main
void PrintMenu(Playlist &, string);

int main () {
    // Prompt the user for the playlist
    string title;
    cout << "Enter playlist's title:" << endl;
    getline (cin, title);
    cout << endl;

    // Create playlist object using the title
    Playlist newPlaylist = Playlist(title);
    
    // Call the print menu function
    PrintMenu(newPlaylist, title);
}

void PrintMenu(Playlist &newPlaylist, string title) {

    // Output the list of options
    cout << title << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl << "Choose an option:" << endl;

    // Take in user's letter of choice using cin
    char option;
    cin >> option;

    // Start a loop, so the user could repeadetly use the menu until they input q, quit.
    while (option == 'a' || option == 'd' || option == 'c' || option == 's' || option == 't' || option == 'o' || option == 'q') {

        // When a specific option is chosen by the user, call the corresponding function to newPlaylist.
        if (option == 'a') {
            newPlaylist.AddSong();
            cout << endl;
        }
        else if (option == 'd') {
            newPlaylist.RemoveSong();
            cout << endl;
        }
        else if (option == 'c') {
            newPlaylist.ChangePosition();
            cout << endl;
        }
        else if (option == 's') {
            newPlaylist.OutPutSongsByArtist();
        }
        else if (option == 't') {
            newPlaylist.OutputTotalSongTime();
            cout << endl;
        }
        else if (option == 'o') {
            newPlaylist.OutputFullPlaylist();
            cout << endl;
        }

        // Exit out of program if user option is q
        else if (option == 'q') {
            exit(1);
        }

    // Looping, using idea of recursion. Print menu after adding the song so the user could enter another choice of option.
    PrintMenu(newPlaylist, title);
    cin >> option;
    }
}
