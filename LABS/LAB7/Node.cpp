#include "Node.h"

Node::Node()
{
    data = "";
    left = 0;
    right = 0;
    height = 0;
}

Node::Node(const string &key)
{
    data = key;
    left = 0;
    right = 0;
    height = 1;
}

string Node::getKey() const 
{
    return data;
}

int Node::getHeight() const
{
    return height;
}

void Node::setHeight(int h) 
{
    height = h;
}

void Node::setLeft(Node *l)
{
    left = l;
}

Node *Node::getLeft() const
{
    return left;
}

void Node::setRight(Node *r)
{
    right = r;
}

Node *Node::getRight() const
{
    return right;
}

