#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
   // Creates a newNode with user's payload input, sets the next to nullptr and returns the newNode 
   Node * newNode = new Node;
   newNode->payload = payload;
   newNode->next = nullptr;
   return newNode;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        if (head == nullptr) {
            head = newNode(name); // initialize head specially
            prev = head; // Previous points to newNode aka head as well since list is empty
        } else {
            prev->next = newNode(name); // list is not empty, make the newNode next to head which is previous as well
            prev = prev->next; // Previous points to the next
        }
    }

    if (prev != nullptr) {
        prev->next = head; // make circular
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
            prev = curr; // keep track of previous node
            curr = curr->next; // moving nodes to the right
        }

        prev->next = curr->next; // delete kth node ; prev/curr => curr prev => 0 prev => 0 prev curr
        delete curr;
        curr = prev->next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

