#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using std::string;

class Node
{
    public:
        Node();
        Node(const string&);
        string getKey() const;
        int getHeight() const;
        void setHeight(int);
        void setLeft(Node *);
        Node *getLeft() const;
        void setRight(Node *);
        Node *getRight() const;
    private: 
        string data;
        Node *left;
        Node *right;
        int height;
};

#endif // __NODE_H__
