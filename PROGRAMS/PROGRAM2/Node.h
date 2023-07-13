#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>

using namespace std;

class Node {

private:
    // Each node in the tree should hold a string and also contain an integer count.
    int count;
    string data;
public:
    // Default constructor
    Node();
    Node(const string &, int);

    // Left and right subtree pointers
    Node *leftChild;
    Node *rightChild;

    // Accessors
    // Returns the count / data of the node
    int GetCount();
    string GetData();

    // Mutators
    // Set the count / data accordingly to the parameter of a node
    void SetCount(int);
    void SetData(const string &);

    // Increases / decreases the count of a node. Need this for Inset and Remove function for BSTree
    void Incr_Count();
    void Decr_Count();

};

#endif
