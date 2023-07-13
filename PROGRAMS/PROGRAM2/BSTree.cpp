#include "BSTree.h"

#include <iostream>
#include <string>

// Default constructor
BSTree::BSTree() {
    root = nullptr; // constructs the tree with root being set to null
}

// Destructor
BSTree::~BSTree() {
    destructor_helper(root);
}

// Private helper function for the destructor
void BSTree::destructor_helper(Node *rootNode) {
    if (rootNode != nullptr) {
        destructor_helper(rootNode->leftChild);
        destructor_helper(rootNode->rightChild);
        delete rootNode;
    }
}

// Copy Assignment Operator
BSTree& BSTree::operator=(const BSTree &rhs) {
    if(this != &rhs){
        root = nullptr;
        while(rhs.root){
            insert(rhs.root->GetData());
        }
    }
    return *this;
}

// Copy constructor
BSTree::BSTree(const BSTree &cpy) {
    root = nullptr;

    while(cpy.root){
        insert(cpy.root->GetData());
    }
}

// Function the return the largest value in the tree. Returns empty string if tree is empty
string BSTree::largest() const {
    Node* rootNode = root;  // root is this->root
    if (rootNode == nullptr) {
        return "";
    }

    while (rootNode->rightChild != nullptr) {
        rootNode = rootNode->rightChild; // While the tree isnt empty, traverse to the rightmost subtree
    }

    return rootNode->GetData();
}

// Function to return the smallest value in the tree. Returns empty string if tree is empty
string BSTree::smallest() const {
    Node* rootNode = root;
    if (rootNode == nullptr) {
        return "";
    }

    while (rootNode->leftChild != nullptr) {
        rootNode = rootNode->leftChild; // While the tree isnt empty, traverse to the leftmost subtree
    }

    return rootNode->GetData();
}

// Function to insert a new node in the BSTree, following the BSTree properties
void BSTree::insert(const string &dataVal) {
    if (root == nullptr) {
        Node *newNode = new Node(dataVal, 1); // If root is null, simply insert a newNode with the dataValue to be inserted with count of 1
        root = newNode;
    }

    else {
        Node *currNode = root;
        if (search(dataVal) == false) { // If node with same value doesn't exist, proceed to insert algorithm
            Node *newNode = new Node(dataVal, 1); // Create a new node to insert with data value and 1 count
            while (currNode) {
                if (dataVal < currNode->GetData()) { // BST properties. If data value to insert is less than root or parent node, go to left subtree
                    if (currNode->leftChild == nullptr) { // If there is space in the left subtree to insert, insert the new node
                        currNode->leftChild = newNode;
                        newNode->SetCount(1);
                        currNode = nullptr;
                    }
                    else {
                        currNode = currNode->leftChild; // Search for left subtree
                    }
                }
                else {
                    if (currNode->rightChild == nullptr) {
                        currNode->rightChild = newNode; // If there is spacei nthe right subtree to insert, insert the new node
                        newNode->SetCount(1);
                        currNode = nullptr;
                    }
                    else {
                        currNode = currNode->rightChild; // Search for right subtree
                    }
                }
            }
        }

        else { // Node with same value exists
            while (currNode) {
                if (dataVal == currNode->GetData()) {
                    currNode->Incr_Count(); // Otherwise simply increase count if the data value to insert is equal to the node's data 
                    currNode = nullptr;
                }
                else if (dataVal < currNode->GetData()) {
                    currNode = currNode->leftChild; // Search left subtree if data value is less than the node's data
                }
                else {
                    currNode = currNode->rightChild; // Search right subtree if data value is less than the node's data
                }
            }
        }
    }
}

void BSTree::remove(const string &key) {
    Node *parNode = nullptr; // Parent node
    Node *currNode = root; // Current node, which starts from root

    if (!search(key)) {  // if value doesn't exist return
        return;
    }

    while (currNode != nullptr) { // While root is not empty, aka the BSTree is not empty
        if (currNode->GetData() == key) { // If the node matches the data (key) to remove
            if (currNode->GetCount() > 1) {
                currNode->Decr_Count(); // If count is more than 1, simply decrease the count
            }

            else if ((currNode->leftChild == nullptr) && (currNode->rightChild == nullptr)) { // Remove node with only left / right child
                if (parNode == nullptr) {
                    root = nullptr; // If parent is null, there is only one node. Remove root
                }
                else if (parNode->leftChild == currNode) {
                    parNode->leftChild = nullptr; //
                }
                else {
                    parNode->rightChild = nullptr;
                }
            }

            else if (currNode->leftChild == nullptr) { // Remove node with two children for left
                if (parNode == nullptr) { 
                    root = currNode->rightChild; 
                }
                else {
                    Node* sucNode = currNode->rightChild; // Set sucessor node to the right child of current node
                    while (sucNode->leftChild != nullptr) {
                        sucNode = sucNode->leftChild;
                    }
                    string removeData = sucNode->GetData();
                    remove(removeData); // Recursive call to remove the data
                    currNode->SetData(removeData); // Set the data back to the sucessor node's data
                }
            }

            else { // Remove node with two children for right
                Node* sucNode = currNode->leftChild;
                while(sucNode->rightChild != nullptr) {
                    sucNode = sucNode->rightChild;
                }
                string removeData = sucNode->GetData();
                remove(removeData); // Recursive call here
                currNode->SetData(removeData);
            }
            return;
        }

        else if (currNode->GetData() < key) {
            parNode = currNode;
            currNode = currNode->rightChild;
        }

        else {
            parNode = currNode;
            currNode = currNode->leftChild;
        }
    }
    return; 
}

bool BSTree::search(const string &key) const {
    return search_helper(root, key); 
}

// Private helper function to search for the node given the key (data), and returns true / false based on if it is found / not found
bool BSTree::search_helper(Node *nodePtr, const string &key) const {
    if (nodePtr == nullptr) {
        return false; // If the node parameter is null , return false. NOT found.
    }

    else if (nodePtr->GetData() > key) {
        return search_helper(nodePtr->leftChild, key); // Left child BST properties; search for left child if key is less than root or prev node
    }

    else if (nodePtr->GetData() < key) {
        return search_helper(nodePtr->rightChild, key); // Right child bst properties, search for right node if prev/root node is greater than key
    }

    else {
        return true; // otherwise the node is found and return true
    }
}

int BSTree::height(const string &key) const {
    Node *nodePtr = root;
    while (nodePtr != nullptr) { // Find the node that we are trying to get the height of
        if (key < nodePtr->GetData()) {
            nodePtr = nodePtr->leftChild;
        }

        else if (key > nodePtr->GetData()) {
            nodePtr = nodePtr->rightChild;
        }

        else {
            break;
        }
    }

    int height = height_helper(nodePtr);
    return height;
}

// Private helper function to recursively find the height of a given node
int BSTree::height_helper(Node* nodePtr) const {
    if (nodePtr == nullptr) {
        return -1;
    }

    int left_height = height_helper(nodePtr->leftChild);
    int right_height = height_helper(nodePtr->rightChild);

    if (left_height > right_height) {
        return left_height + 1;
    }
    else {
        return right_height + 1;
    }
}

void BSTree::preOrder() const {
    preOrder_helper(root);
}

// Private helper function to recursively print tree values in pre order
void BSTree::preOrder_helper(Node* rootNode) const {
    if (rootNode != nullptr) { // If tree isn't empty, visit the root, traverse the left subtree, then traverse the right subtree while printing the values
        cout << rootNode->GetData() << "(" << rootNode->GetCount() << "), ";
        preOrder_helper(rootNode->leftChild);
        preOrder_helper(rootNode->rightChild); 
    }
}

void BSTree::postOrder() const {
    postOrder_helper(root);
}

// Private helper fnction to recursively print tree values in post order
void BSTree::postOrder_helper(Node* rootNode) const {
    if (rootNode != nullptr) {  // If tree isn't empty, traverse the left subtree, traverse the right subtree, then visit the root while printing the values
        postOrder_helper(rootNode->leftChild);  
        postOrder_helper(rootNode->rightChild);
        cout << rootNode->GetData() << "(" << rootNode->GetCount() << "), "; 
    }
}

void BSTree::inOrder() const {
    inOrder_helper(root);
}

// Private helper function to recursively print the tree values in order from smallest to largest
void BSTree::inOrder_helper(Node* rootNode) const {
    if (rootNode != nullptr) {  // If tree exists, traverse left subtree, visit the root, traverse the right subtree while printing the values
        inOrder_helper(rootNode->leftChild);
        cout << rootNode->GetData() << "(" << rootNode->GetCount() << "), "; 
        inOrder_helper(rootNode->rightChild);
    }
}
