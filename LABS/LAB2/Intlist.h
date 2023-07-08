#ifndef INTLIST_H
#define INTLIST_H

#include <iostream>

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
    private: 
        // Dummy nodes to avoid dealing with special cases
        IntNode* dummyHead;
        IntNode* dummyTail;

    public:
        // Default constructor, initializes an empty list with dummy head and dummy tail
        IntList();

        // Destructor, deallocates all remaining dynamically allocated memory
        ~IntList();

        // Copy constructor and assignment operator, BIG 3
        IntList(const IntList &cpy);
        
        IntList& operator=(const IntList &rhs);

        // Following void functions must be an O(1) operation
        // Inserts a data value within a new node to the front of the list
        void push_front(int value);

        // Removes a node at the front of the list. Does nothing if list is empty
        void pop_front();

        // Inserts a data value within a new node to the end of the list
        void push_back(int value);

        // Removes a node at the end of the list. Does nothing if list is empty
        void pop_back();

        // Returns true if list does not store any real values (list only has dummyhead and dummytail).
        bool empty() const;

        // A global friend function that outputs to the stream all of the integer values within the list on a single line, each separated by a space.
        // This function does NOT send to the stream a newline or space at the end.
        friend ostream & operator<<(ostream &out, const IntList &rhs);

        // Prints a single line of all of the int values stored in the list in reverse, each separated by a space. Does not output a newline or space at the end.
        void printReverse() const;

};

#endif
