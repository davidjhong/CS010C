#include "Node.h"

#include <iostream>
#include <string>

using namespace std;

// Default constructor. Initializes count and data to 0 and "", both left and right child pointers to nullptr
Node::Node() {
    count = 0;
    data = "";
    leftChild = nullptr;
    rightChild = nullptr;
}

// Parameterized constructor. Sets count and data to input values. Both left and right child are still nullptr
Node::Node(const string &val, int cnt) {
    count = cnt;
    data = val;
    leftChild = nullptr;
    rightChild = nullptr;
}

// Accessors
// Gets (returns) the count of the node
int Node::GetCount() {
    return count;
}

// Returns the data, string value, of the node
string Node::GetData() {
    return data;
}

// Mutators
// Sets (assigns) the count of the node with input value
void Node::SetCount(int cnt) {
    count = cnt;
}

// Sets the data of the node with input string value
void Node::SetData(const string &val) {
    data = val;
}

// Increases / decreases count of the nodes
void Node::Incr_Count() {
    count += 1;
}

void Node::Decr_Count() {
    count -= 1;
}
