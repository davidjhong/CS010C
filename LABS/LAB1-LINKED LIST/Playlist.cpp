#include "Playlist.h"

using namespace std;

// Default constructor initialized to none and 0
PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

// Parameterized constructor; initialize private values with inputted values
PlaylistNode::PlaylistNode(string id, string name, string artist, int length) {
    uniqueID = id;
    songName = name;
    artistName = artist;
    songLength = length;
    nextNodePtr = 0;
}

// Inserts a new node after the current one 
// before: this -- next
// after: this -- node -- next

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    // Create a temporary node and initialize it to nullptr
    PlaylistNode* tempNext = 0;

    // Set the temporary node to the next value of implicit node 
    tempNext = this->nextNodePtr;

    // Set the next value of the implicit node to the explicit node; this -- node -- ?
    this->nextNodePtr = node;

    // Finally, make the explicit node's next point to temporary node; this -- node -- next 
    node->nextNodePtr = tempNext;

}

// Sets the next node pointer to the inputted node value; mutator function
void PlaylistNode::SetNext(PlaylistNode* nextNode) {
    nextNodePtr = nextNode;
}

// Accessor functions - should be CONST. returns the corresponding values, "Gets" the values and return it
string PlaylistNode::GetID() const {
    return uniqueID;
}

string PlaylistNode::GetSongName() const {
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

// Funcition to print node(song) information
void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

// Default constructor for playlist class. Head and tail = nullptr
Playlist::Playlist() {
    title = "";
    head = 0;
    tail = 0;
}

// Parameterized constructor
Playlist::Playlist(string newTitle) {
    title = newTitle;
    // head and tail are still nullptr by default
    head = 0;
    tail = 0;
}

// Destructor
Playlist::~Playlist() {
    PlaylistNode* curr = head;
    PlaylistNode* next;
    while (curr != 0) {
        next = curr->GetNext();
        delete curr;
        curr = next;
    }
    head = 0;
    tail = 0;
}

// Copy assignment and copy constructor
Playlist::Playlist(const Playlist &cpy) {
    head = 0;
    tail = 0;

    for(PlaylistNode* i = cpy.head; i != 0; i = i->GetNext()){
        if (head == 0 && tail == 0){
            head = i;
            tail = i;
            // Basically pushing back the node to the end of list
            head->InsertAfter(tail);
        } 
        else {
            tail->InsertAfter(i);
            tail = i;
        }
    }
}

// Copy Constructor
Playlist & Playlist::operator=(const Playlist &rhs) {

    // Checking if list is empty
    if (rhs.head == 0 && rhs.tail == 0) {
        // Set implicit list's head and tail to nullptr; "Copying" the node thats inputted
        head = 0;
        tail = 0;
    }
    else if (this != &rhs){
        for (PlaylistNode* i = rhs.head; i != 0; i = i->GetNext()){
            if (head == 0){
                head = i;
                tail = i;
                head->InsertAfter(tail);
            } 
            else {
                tail->InsertAfter(i);
                tail = i;
            }
        }
    }
    return *this; 
}

// Implement options for print menu
void Playlist::OutputFullPlaylist() {

    // Output the whole playlist
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;

    // If list is empty, output
    if (head == 0 && tail == 0) {
        cout << "Playlist is empty" << endl;
    }
    else {

        // Initialize position to 1 so the option can print out the songs in order
        int position = 1;
        PlaylistNode* curr = head;
        for (curr = head; curr != 0; curr = curr->GetNext()) {
            cout << position << "." << endl;
            curr->PrintPlaylistNode();

            // Only print newline if the song is not at the end of the list
            if (curr != tail) {
                cout << endl;
            }

            //Keep incrementing position as the loop continues onto the next
            position++;
            }
    }
}
        
void Playlist::AddSong() {

    // Add song to list
    string id = "", name = "", artist ="";
    int length = 0;

    // Prompt user for id, name, artist, and song length
    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> id;
    cout << "Enter song's name:" << endl;

    // Ignore endline
    cin.ignore();
    getline(cin, name);
    cout << "Enter artist's name:" << endl;
    getline(cin, artist);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;

    // Create a new parameterized node that contains all the information above to the end of the list
    PlaylistNode* newNode = new PlaylistNode(id, name, artist, length);

     // If the list is not empty, push the new node back to the list; else simply set the head and tail to the new node
    if (head == 0 && tail == 0) {
        tail = newNode;
        head = tail;
    }
    else {
        tail->SetNext(newNode);
        tail = newNode;
    }   
}
        
void Playlist::RemoveSong() {

    // Remove song from list
    string name = "";
    cout << "REMOVE SONG" << endl;
    string id = "";
    cout << "Enter song's unique ID:" << endl;
    cin >> id;

    // Check if list is empty, output error and exit out of else if statement
    if (head == 0 && tail == 0) {
        cout << "Error" << endl;
        return;
    }

    // Check if list has one song, delete that song and set head and tail back to nullptr
    else if (head == tail) {
        PlaylistNode* curr = head;
        cout << "\"" << curr->GetSongName() << "\"" << " removed." << endl;
        delete curr;
        head = 0;
        tail = 0;
    }
    else {

        // Previous node to keep track and prevent memory leak
        PlaylistNode* prev = head;
        PlaylistNode* curr = head->GetNext();
        for (curr = head->GetNext(); curr != 0; curr = curr->GetNext()) {
            if (curr->GetID() == id) {
                cout << "\"" << curr->GetSongName() << "\"" << " removed." << endl;
                // Victim node that will point to the node that will be deleted
                PlaylistNode* victim = curr;
                // say - is a node... - - prev curr - -
                // - - prev victim - -; prev points to the next node of victim, then victim gets deleted, then prev->next becomes curr so the loop can continue
                prev->SetNext(curr->GetNext());
                // Deallocate victim, or "curr"
                delete victim;
                curr = prev->GetNext();
                name = curr->GetSongName();
            }
        }
    }
}
        
void Playlist::ChangePosition() {

    // Change position of song in the list. First requires value of current position and the new position the user wants to swap orders with
    int currentPosition = 0, newPosition = 0;
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    cin >> currentPosition;
    cout << "Enter new position for song:" << endl;
    cin >> newPosition;
    
    // If current and new position is same, do nothing and exit out of option
    if (currentPosition == newPosition) {
        return;
    }

    // If list is empty, output error and exit out of the option
    if (head == 0 && tail == 0) {
        cout << "Error, list is empty" << endl;
        return;
    }

    // Count the total number of songs in the list
    int playlistLength = 0;
    for (PlaylistNode* curr = head; curr != 0; curr = curr->GetNext()) {
        playlistLength++;
    }

    // If user enters a new position that is not within 1-n (the number of nodes)
    if (newPosition < 1) {
        newPosition = 1;
    }
    else if (newPosition > playlistLength) {
        newPosition = playlistLength;
    }

    // Find the node that needs to be moved; aka the song at the current position.
    PlaylistNode *curr = head;
    PlaylistNode *prev = 0;
    for (int i = 1; curr != 0 && i < currentPosition; i++) {
        prev = curr;
        curr = curr->GetNext();
    }

    // Inserting the song at the new position
    //Check if node is found at given position first
    if (curr != 0) {
        // Remove the song at from the current list and later insert it into the specific position in the list. 
        // No deallocating after removing the node, we simply insert it back to the new position
        if (prev != 0) {
            prev->SetNext(curr->GetNext());
        }
        else {
            head = curr->GetNext();
        }
        // if tail node is removed
        if (curr == tail) {
            tail = prev;
        }

        // Locate new position and insert the new song (node) at the new position
        PlaylistNode *newCurr = head;
        PlaylistNode *newPrev = 0;
        for (int i = 1; newCurr != 0 && i < newPosition; i++) {
            newPrev = newCurr;
            newCurr = newCurr->GetNext();
        }

        // Insert in located position
        if (newPrev != 0) {
            newPrev->InsertAfter(curr);
        }
        else {
            curr->SetNext(head);
            head = curr;
        }
        if (newCurr == 0) {
            tail = curr;
        }    
    }
    
    //Node not found at given position, error
    else {
        cout << "Error" << endl;
        return;
    }

    // Finally, output message
    cout << "\"" << curr->GetSongName() << "\" moved to position " << newPosition << endl;
    }

        
void Playlist::OutPutSongsByArtist() {

    // Output song by specific artist name prompted by user
    string artist = "";
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;

    // Ignore endline before getline
    cin.ignore();
    getline(cin, artist);
    cout << endl;
    int position = 1;

    // Make sure list is NOT empty
    if (head != 0) {
        for (PlaylistNode* curr = head; curr != 0; curr = curr->GetNext()) {
            //Loop through the list to find the artist name that matches the user input. If not, exit out. If found, output the song information using PrintPlaylistNode Function
            if (curr->GetArtistName() == artist) {
                cout << position << "." << endl;
                curr->PrintPlaylistNode();
                cout << endl;
            }
            position++;
        }
    }
}
        
void Playlist::OutputTotalSongTime() {
    // Add song length for every song in list. Initialize totalLength and length variables to 0
    int totalLength = 0;
    int length = 0;

    // Loop through the list, get the length for each song, assign length to the length for each song, and add it to totalLength.
    for (PlaylistNode* curr = head; curr != 0; curr = curr->GetNext()) {
        length = curr->GetSongLength();
        totalLength += length;
    }

    // Output totalLength aka total time of the playlist in seconds
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    cout << "Total time: " << totalLength << " seconds" << endl;
}
