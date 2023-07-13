#include "Node.h"
#include <string>

using namespace std;

// Default Constructor
Node::Node() 
{
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
}

// Parameterized constructor
Node::Node(const string &data) 
{
    small = data;
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
}

// Returns true if node has two strings
bool Node::hasTwoStrings() const 
{
    return !large.empty();
}
