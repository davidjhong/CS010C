#include "IntList.h"

using namespace std;

// Default Constructor
IntList::IntList() {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

// Returns true if list is empty
bool IntList::empty() const {
    return (dummyHead->next == dummyTail);
}

// Destructor using pop back
IntList::~IntList()
{
    IntNode *curr = dummyHead->next; 

    while(curr != dummyTail){
        IntNode *victim = curr;
        delete victim;
        curr = curr->next;
    }

    delete dummyHead;
    delete dummyTail;
}

// Copy Constructor
IntList::IntList(const IntList &cpy) {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);

    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;

    for (IntNode* curr = cpy.dummyHead->next; curr != cpy.dummyTail; curr = curr->next) {
        push_back(curr->data);
    }
}

// Copy assignment operator
IntList& IntList::operator=(const IntList &rhs) {
    if (empty()) {
        dummyHead = 0;
        dummyTail = 0;
    } 
    else if (this != &rhs) {
        dummyHead = new IntNode(0);
        dummyTail = new IntNode(0);

        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;

    for (IntNode* curr = rhs.dummyHead->next; curr != rhs.dummyTail; curr = curr->next) {
        push_back(curr->data);
    }

    }

    return *this;
}


// Inserts a data value within a new node to the front of the list, O(1) operation
void IntList::push_front(int value) {
    IntNode *newNode = new IntNode(value);
    newNode->next = dummyHead->next;
    newNode->prev = dummyHead;
    dummyHead->next->prev = newNode;
    dummyHead->next = newNode;
}

// Removes a node at the front of the list. Does nothing if list is empty
void IntList::pop_front() {
    // If list is empty do nothing
    if (empty()) {
        return;
    }
    else {
        IntNode *victim = dummyHead->next; // dummyHead - - - -
        dummyHead->next = victim->next; // dummyHead victim - - -
        victim->next->prev = dummyHead; // dummyHead - - -
        delete victim;
    }
}

// Inserts a data value within a new node to the end of the list
void IntList::push_back(int value) {
    IntNode *newNode = new IntNode(value);
    newNode->next = dummyTail;
    newNode->prev = dummyTail->prev;
    dummyTail->prev->next = newNode;
    dummyTail->prev = newNode;
}

// Removes a node at the end of the list. Does nothing if list is empty
void IntList::pop_back() {
    if (empty()) {
        return;
    }
    else {
        IntNode *victim = dummyTail->prev; // - - - - victim dummyTail
        dummyTail->prev = victim->prev; // - - - dummyPrev victim dummyTail
        victim->prev->next = dummyTail; // - - - - victim/dummytail
        delete victim;
    }
}

// A global friend function that outputs to the stream all of the integer values within the list on a single line, each separated by a space.
// This function does NOT send to the stream a newline or space at the end.
ostream & operator<<(ostream &out, const IntList &rhs) {
    IntNode *curr = rhs.dummyHead->next; // Start from head
    while (curr != rhs.dummyTail) { // Loop until list reaches end while ouputting each node
        if (curr->next == rhs.dummyTail) {
            out << curr->data;
        }
        else {
            out << curr->data << " "; // does not send endline or space at the end
        }
        curr = curr->next;
    }
    return out;
}

// Prints a single line of all of the int values stored in the list in reverse, each separated by a space. Does not output a newline or space at the end.
void IntList::printReverse() const {
    IntNode *curr = dummyTail->prev; // Start from tail
    while (curr != dummyHead) {
        if (curr->prev == dummyHead) {
            cout << curr->data;
        }
        else {
            cout << curr->data << " ";
        }
        curr = curr->prev;
    }
}
