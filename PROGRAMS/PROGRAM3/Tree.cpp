#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

// Default Constructor
Tree::Tree() 
{
    root = 0;
}

// Destructor
Tree::~Tree()
{
    destruct(root);
}

// Destructor helper
void Tree::destruct(Node *curr) // Helper function that recursively goes through the left, middle, and right before deleting the node
{
    if (curr != 0) 
    {
        destruct(curr->left);
        destruct(curr->middle);
        destruct(curr->right);
        delete curr;
    }
}

// Function to insert a node with the user data in the 2-3 tree
void Tree::insert(const string &data)
{
    if (root == 0)
    {
        root = new Node(data); // If root is empty, simply create a new node with input data and insert it to root then return
        return;
    }
    else // Otherwise set curr to root
    {
        Node* curr = root;
        while (curr->left) // While left child exists
        {
            if (curr->hasTwoStrings()) // If curr node has two strings
            {
                if (data < curr->small) // If data is smaller than curr's small val, move curr to left
                {
                    curr = curr->left;
                }
                else if (data > curr->large) // If data is greater than curr's small val, move curr to right
                {
                    curr = curr->right;
                }
                else // Otherwise curr moves to the middle
                {
                    curr = curr->middle;
                }
            }
            else // Does not have two strings
            {
                if (data < curr->small) // Perform same operations as above, but cannot move right since there is no large value
                {
                    curr = curr->left;
                }
                else
                {
                    curr = curr->middle;
                }
            }
        } // End loop to move curr when left is empty

        if (curr->hasTwoStrings()) // If curr has two strings
        {
            string small;
            string middle; // Finding small middle and large string values 
            string large;

            if (data < curr->small) // If data is greater than curr's small value, small = data, middle become curr's small value, and large becomes curr's large value
            {
                small = data;
                middle = curr->small;
                large = curr->large;
            }
            else // Else if data is larger than small
            {
                small = curr->small;
                if (data > curr->large) // Data is larger than curr's large, set data to the largest point
                {
                    middle = curr->large;
                    large = data;
                }
                else // Data is smaller than curr's large value, set middle to data and large to curr's large
                {
                    middle = data;
                    large = curr->large;
                }
            }

            Node* smallNode = new Node(small); // Create new nodes to insert
            Node* largeNode = new Node(large);

            curr->small = middle;
            curr->large = "";
            curr->left = smallNode; // Set (insert) the small large and children values accordingly
            curr->middle = largeNode;
            curr->right = 0;

            smallNode->parent = curr;
            largeNode->parent = curr;

            moveUp(curr); // Move up the curr node
        }
        else // Curr only has one string aka small 
        {
            if (data < curr->small) // Simply set large to curr->small and small to data if data has smaller value than curr->small
            {
                curr->large = curr->small;
                curr->small = data;
            }
            else // Otherwise insert data into large
            {
                curr->large = data;
            }
        }
    }
}

// Function to remove a node based on user input
void Tree::remove(const string &data)
{
    Node* curr = root;
    while (curr)
    {
        if (curr->small == data || (curr->hasTwoStrings() && curr->large == data))
        {
            break; // Break out of loop if the data to remove is found in node's small or large. Return
        }
        else // Move the node accordingly to find the data we are trying to remove
        {
            if (data < curr->small)
            {
                curr = curr->left;
            }
            else // data is bigger than small, so move right or middle according to properties of 2-3 trees
            {
                if (curr->hasTwoStrings() && curr->large < data)
                {
                    curr = curr->right;
                }
                else
                {
                    curr = curr->middle;
                }
            }
        }
    }

    if (curr->hasTwoStrings()) // Found the node to delete. If curr has two string values, proceed to following if else
    {
        if (data == curr->small) // Data is equal to curr small. Shift small to large and delete large
        {
            curr->small = curr->large;
            curr->large = "";
        } 
        else // Otherwise data is greater than small or is set to large, so delete large.
        {
            curr->large = "";
        }
    }
    else // One string 
    {
        Node* parentNode = curr->parent;
        if (parentNode) // Parent exists
        {
            if (data < parentNode->small) // If data is smaller than parentNode's small value, set parent's left and middle child to null while setting it's large to its middle child's small value
            {
                parentNode->left = 0;
                parentNode->large = parentNode->middle->small;
                parentNode->middle = 0;
            }
            else // Data is greater than small value
            {
                parentNode->middle = 0;
                parentNode->large = parentNode->small;
                parentNode->small = parentNode->left->small;
                parentNode->left = 0;
            }
        }
        else // Parent is null, we remove the root.
        {
            Node* victim = new Node(); // Node to delete, "temporary" node
            if (root->left)
            {
                victim->small = root->left->small;
                victim->large = root->middle->small;
                root = victim;
            }
            else
            {
                root = 0;
            }
        }
    }
}

void Tree::preOrder() const 
{
    preOrder(root);
    cout << endl;
}

void Tree::preOrder(Node* curr) const 
{
    if (curr) // While root or the node to print exists
    {
        if (curr->hasTwoStrings()) // If the root or the following node to print has two strings, do preOrder on all three children while printing large and small values
        {
            cout << curr->small << ", ";
            preOrder(curr->left);
            cout << curr->large << ", ";
            preOrder(curr->middle);
            preOrder(curr->right);
        }
        else // Otherwise, only print left and middle with small values as large does not exist.
        {
            cout << curr->small << ", ";
            preOrder(curr->left);
            preOrder(curr->middle);
        }
    }
}

void Tree::inOrder() const 
{
    inOrder(root);
    cout << endl;
}

void Tree::inOrder(Node* curr) const
{
    if (curr) // If root or the node to print exists, print left and middle children's small values first
    { 
        inOrder(curr->left); 
        cout << curr->small << ", ";
        inOrder(curr->middle);

        if (curr->hasTwoStrings()) // Check if the root or the node to print has two strings, in this case, if true, print large and go to the right child
        {
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}


void Tree::postOrder() const 
{
    postOrder(root);
    cout << endl;
}

void Tree::postOrder(Node* curr) const
{
    if (curr) // While the root exists
    {
        if (curr->hasTwoStrings()) // If the root or the following node to print has two strings, do postOrder on all three children while printing large and small values
        {
            postOrder(curr->left);
            postOrder(curr->middle);
            cout << curr->small << ", ";
            postOrder(curr->right);
            cout << curr->large << ", ";

        }
        else // Otherwise, only print left and middle with small values as large does not exist.
        {
            postOrder(curr->left);
            postOrder(curr->middle);
            cout << curr->small << ", ";
        }
    }
}

// Function to search for the node containing the data
bool Tree::search(const string &data) const
{
    return search(root, data); // Call the recursive helper function
}

// Recursive helper for search
Node *Tree::search(Node *curr, const string & data) const 
{
    if (curr == 0) 
    {
        return 0; // If node does not exist return null (false)
    }
    else
    {
        if (data == curr->small)
        {
            return curr; // Data matches node's small. Return the node as we found it
        }
        if (data < curr->small)
        {
            return search(curr->left, data); // Recursive call to search left child if data is smaller than curr's small
        }
        else if (curr->large.empty())
        {
            return search(curr->right, data); // Recursive call to search right child if curr does not have a large
        }
        else // Else if large exists
        {
            if(data == curr->large) 
            {
                return curr; // If data matches large value, return the node
            }
            else if(data < curr->large)
            {
                return search(curr->middle, data); // Recursive call to search left child
            }
            else
            {
                return search(curr->right, data); // Recursive call to search right child. This case data is larger than large string value
            }
        }
    }
}

// Function shift the node up into the correct place. The node in the parameter needs to be moved into its parent and always has only 1 node
void Tree::moveUp(Node* curr)
{
    if (curr->parent) // Curr's parent exists
    {
        Node* parentNode = curr->parent;
        if (parentNode->hasTwoStrings()) // If the parent node has two strings
        {
            if (parentNode->small > curr->small) // Parent's smaller value is greater than curr's small value, perform left shift
            {
                Node* largeNode = new Node();
                largeNode->left = parentNode->middle;
                largeNode->left->parent = largeNode;
                largeNode->middle = parentNode->right;
                largeNode->middle->parent = largeNode;
                largeNode->small = parentNode->large;

                parentNode->left = curr;
                parentNode->middle = largeNode;
                parentNode->right = 0;
                parentNode->large = "";

                largeNode->parent = parentNode;
            }
            else if (parentNode->large < curr->small) // Parent node's large value is smaller than curr's small value, perform left shift
            {
                Node* smallNode = new Node();
                smallNode->left = parentNode->left;
                smallNode->left->parent = smallNode;
                smallNode->middle = parentNode->middle;
                smallNode->middle->parent = smallNode;
                smallNode->small = parentNode->small;

                parentNode->left = smallNode;
                parentNode->middle = curr;
                parentNode->right = 0;
                parentNode->small = parentNode->large;
                parentNode->large = "";

                smallNode->parent = parentNode;
            }
            else // Otherwise begin shifting up values 
            {
                Node* smallNode = new Node(); // Shifting small node
                smallNode->small = parentNode->small;
                smallNode->left = parentNode->left; 
                smallNode->left->parent = smallNode;
                smallNode->middle = curr->left;
                smallNode->middle->parent = smallNode;

                Node* largeNode = new Node(); // Shifting large node
                largeNode->small = parentNode->large;
                largeNode->left = curr->middle;
                largeNode->left->parent = largeNode;
                largeNode->middle = parentNode->middle;
                largeNode->middle->parent = largeNode;

                parentNode->left = smallNode; // Resetting values to empty and small
                parentNode->middle = largeNode;
                parentNode->right = 0;
                parentNode->small = curr->small;
                parentNode->large = ""; 

                smallNode->parent = parentNode;
                largeNode->parent = parentNode;

                delete curr; // Delete parameter
            }

            moveUp(parentNode); // Recursive call to move up
        }
        else // Parent node has one string
        {
            if (parentNode->small > curr->small) // Parent node's small value is greater than curr's small value; left
            {
                parentNode->large = parentNode->small;
                parentNode->small = curr->small;

                parentNode->left = curr->left;
                parentNode->middle = curr->middle;
                parentNode->right = 0;
            }
            else // Parent node's small value is lesser than curr's small value; middle
            {
                parentNode->large = curr->small;

                parentNode->middle = curr->left;
                curr->left->parent = parentNode;
                parentNode->right = curr->middle;
                curr->middle->parent = parentNode;
            }

            curr->left->parent = parentNode;
            curr->middle->parent = parentNode;
            delete curr; // Delete parameter
        }
    }
}

