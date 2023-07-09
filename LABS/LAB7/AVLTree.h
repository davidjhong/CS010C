#ifndef __AVLTree_H__
#define __AVLTree_H__

#include "Node.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>


using namespace std;

class AVLTree {
    public:
        AVLTree(); // Default Constructor
        ~AVLTree(); // Destructor
        void insert(const string &); //Insert an item to the binary search tree and perform rotation if necessary.
        int balanceFactor(Node *); //Return the balance factor of a given node.
        void printBalanceFactors(); //Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.
        void visualizeTree(const string &); // Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.
    private:
        Node *root = 0;
        void destruct(Node *);
        Node *insert(Node *, const string &);
        Node *rotate(Node *, const string &, int); //Implement four possible imbalance cases and update the parent of the given node.
        Node *rotateLeft(Node *); //Rotate the subtree to left at the given node and returns the new subroot.
        Node *rotateRight(Node *); //Rotate the subtree to right at the given node and returns the new subroot.
        void printBalanceFactors(Node *);
        void visualizeTree(ofstream &, Node *);
        int height(Node*) const;
};

#endif
