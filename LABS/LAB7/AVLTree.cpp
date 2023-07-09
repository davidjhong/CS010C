#include "AVLTree.h"

using namespace std;

// Default Constructor
AVLTree::AVLTree() {
    root = 0;
}

// Destructor
AVLTree::~AVLTree()
{
    destruct(root);
}

// Destructor Helper
void AVLTree::destruct(Node *curr)
{
    if (curr != 0) 
    {
        destruct(curr->getLeft());
        destruct(curr->getRight());
        delete curr;
    }
}

// Function to return the height
int AVLTree::height(Node *node) const
{
    if (node == 0)
    {
        return 0;
    }
    return node->getHeight();
}

// Function to find the balance factor
int AVLTree::balanceFactor(Node *node)
{
    if (node == 0)
    {
        return 0;
    }

    return (height(node->getLeft()) - height(node->getRight()));
}

void AVLTree::insert(const string &key)
{
    root = insert(root, key);
}

// Recursive insert helper
Node *AVLTree::insert(Node *node, const string &key)
{
    if (node == 0)
    {
        Node *newNode = new Node(key);
        return newNode; // If node (root) is null insert at root
    }

    if (key < node->getKey())
    {
        node->setLeft(insert(node->getLeft(), key));
    }
    else if (key > node->getKey())
    {
        node->setRight(insert(node->getRight(), key));
    }
    else
    {
        return node;
    }

    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight()))); // Update the height using max function (implemented in algorithm)

    int balance = balanceFactor(node);

    if (balance < -1 || balance > 1) // Not balanced so rotate
    {
        return rotate(node, key, balance);
    }

    return node; // Return unchanged node pointer
}

// Function to rotate if tree is unbalanced
Node *AVLTree::rotate(Node *node, const string &key, int balance)
{
    // Four cases if node is unbalanced
    // left left case
    if (balance > 1 && key < node->getLeft()->getKey())
    {
        return rotateRight(node);
    }
    // left right case
    if (balance > 1 && key > node->getLeft()->getKey()) 
    {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }
    // right right case
    if (balance < -1 && key > node->getRight()->getKey()) 
    {
        return rotateLeft(node);
    }
    // right left case
    if (balance < -1 && key < node->getRight()->getKey())
    {   
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    return node;
}

Node *AVLTree::rotateRight(Node *node)
{
    Node *lrc = node->getLeft();
    Node *x = lrc->getRight();

    // Rotation
    lrc->setRight(node);
    node->setLeft(x);

    // Updating heights
    node->setHeight(max(height(node->getLeft()), height(node->getRight()) + 1));
    lrc->setHeight(max(height(lrc->getLeft()), height(lrc->getRight()) + 1));

    // Return new root (node)
    return lrc;
}

Node *AVLTree::rotateLeft(Node *node)
{
    Node *lrc = node->getRight();
    Node *x = lrc->getLeft();

    // Rotation
    lrc->setLeft(node);
    node->setRight(x);

    // Updating heights
    node->setHeight(max(height(node->getLeft()), height(node->getRight()) + 1));
    lrc->setHeight(max(height(lrc->getLeft()), height(lrc->getRight()) + 1));

    // Return new root (node)
    return lrc;
}

void AVLTree::visualizeTree(const string &outputFilename)
{
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open())
    {
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *curr)
{
    if(curr){
        if(curr->getLeft()){
            visualizeTree(outFS,curr->getLeft());
            outFS<< curr->getKey() <<" -> " << curr->getLeft()->getKey() << ";" << endl;    
        }

        if(curr->getRight()){
            visualizeTree(outFS,curr->getRight());
            outFS<< curr->getKey() <<" -> " << curr->getRight()->getKey() <<";"<<endl;    
        }
    }
}

void AVLTree::printBalanceFactors(Node *n) { //helper function, print inorder (left, print, right)
    if (n == NULL) {
        return;
    }
    else {
        printBalanceFactors(n->getLeft());
        cout << n->getKey()<< "(" << balanceFactor(n) << "), ";
        printBalanceFactors(n->getRight());
        }
}

void AVLTree::printBalanceFactors() { //pass root and call helper fn
    printBalanceFactors(root);
}
