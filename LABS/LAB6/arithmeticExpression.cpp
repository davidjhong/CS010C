#include "arithmeticExpression.h"
#include <iostream>
#include <cstdlib>
#include <stack>
#include <sstream>
#include <fstream>

//  Implementation of the functions priority, infix_to_postfix and visualizeTree
int arithmeticExpression::priority(char op)
{
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix()
{
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename)
{
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

// Default constructor; Initializes an empty tree and sets the infixExpression to the value of parameter passed in.
arithmeticExpression::arithmeticExpression(const string &expression) : infixExpression(expression), root(nullptr)
{
}

// Function that converts the infixExpression to its equivalent postfix string and then generates the tree and assigns the root node to the root data field. The key for the first node is 'a', 'b' for the second node and so on.
void arithmeticExpression::buildTree() 
{
    string postfixExpression = infix_to_postfix();
    stack <TreeNode*> s;
    
    for(unsigned i = 0; i < postfixExpression.length(); i++){ // Traverse through the whole expression
        TreeNode* T = new TreeNode(postfixExpression.at(i), 'a' + i);
        if(priority(postfixExpression.at(i)) == 0){   // If priority is 0 (first) then push T 
            s.push(T);
        }
        else{ // Otherwise perform subsequent operations 
            T->right = s.top();
            s.pop();
            T->left = s.top();
            s.pop();
            s.push(T);
        }
    }
    root = s.top();
}

/* Calls the recursive infix function. */
void arithmeticExpression::infix()
{
    if (root == nullptr) { // if root doesn't exist, return
        return;
    }
    else {
        infix(root); // Call the recursive function if root exists
    }
}

/* Helper function that outputs the infix notation of the arithmetic expression tree by performing the inorder traversal of the tree.
An opening and closing parenthesis must be added at the 
beginning and ending of each expression. */
void arithmeticExpression::infix(TreeNode *nodePtr) 
{
    if (nodePtr != nullptr){  //checks if tree is empty
        if (nodePtr->left != nullptr || nodePtr->right != nullptr){    // Checks if node exists which then prints out an opening parenthesis
            cout << '(';
        }
        infix(nodePtr->left); // inOrder traversal
        cout << nodePtr->data;
        infix(nodePtr->right);
        if (nodePtr->left != nullptr || nodePtr->right != nullptr ){
            cout << ')';
        }
    }
}

/* Calls the recursive prefix function. */
void arithmeticExpression::prefix()
{
    if (root == nullptr) {
        return;
    }
    else {
        prefix(root);
    }
}

/* Helper function that outputs the prefix notation of the arithmetic expression tree
by performing the preorder traversal of the tree. */
void arithmeticExpression::prefix(TreeNode *nodePtr)
{
    if (nodePtr) {
        cout << nodePtr->data;
        prefix(nodePtr->left);
        prefix(nodePtr->right);
    }
    else {
        return;
    }
}

/* Calls the recursive postfix function. */
void arithmeticExpression::postfix()
{
    if (root == nullptr) {
        return;
    }
    else {
        postfix(root);
    }
}

/* Helper function that outputs the postfix notation of the arithmetic expression tree
by performing the postorder traversal of the tree. */
void arithmeticExpression::postfix(TreeNode *nodePtr)
{
   if (nodePtr) {
        postfix(nodePtr->left);
        postfix(nodePtr->right);
        cout << nodePtr->data;
    }
    else {
        return;
    }
}

/* Helper function for generating the dotty file. This is a recursive function. */
void arithmeticExpression::visualizeTree(ofstream & outFS, TreeNode* node) 
{
    if(node->left != nullptr){   // If left node isn't empty recursively prints out the key
        outFS << "\t" << node->key << " -> " << node->left->key << endl;
        outFS << "\t" << node->key << " -> " << node->right->key << endl;
        visualizeTree(outFS, node->left);
        visualizeTree(outFS, node->right);
    }
}
