#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class stack {
    public:
    static const int MAX_SIZE = 20; // MAX_SIZE will always be 20, STATIC CONSTANT
    // Private data
    private:
        T data[MAX_SIZE]; // An array with maximum size 20
        int size; // size , stores the current number of elements in the stack.
    // Public data
    public:
        stack() {
            size = 0; // "constructor". constructs an empty stack, initializes size to 0.
        }
        
        void push (T val) {
            if (size == MAX_SIZE) {
                throw overflow_error("Called push on full stack."); //Throw overflow error if size is full
            }
            
            else {
            // Otherwise add new value to size position and increment the size
                data[size] = val;
                size++;
            }
        }

        bool empty() {
            return (size == 0); // returns true if size is 0, aka empty.
        }

        void pop() {
            // Throw out of range exception if stack is empty
            if (empty()) {
                throw out_of_range("Called pop on empty stack.");
            }
            
            else {
            // Otherwise, decrement size by 1
                size--;
            }
        }

        void pop_two() {
            // Throw out of range exception if stack is empty or size 1
            if (empty()) {
                throw out_of_range("Called pop_two on empty stack.");
            }

            else if (size == 1) {
                throw out_of_range("Called pop_two on a stack of size 1.");
            }

            else {
                size -= 2; // Pop two; decrement size by two
            }
        }

        T top() {
            if (empty()) {
                throw underflow_error("Called top on empty stack."); // If empty, throw underflow error exception / message 
            }

            return data[size-1]; // return the "top" element on the stack, which is the item at size-1 index
        }
};

#endif

// ** try catch method worked, however not sure if we can call overflow, underflow outofrange error instead of runtime error so used throw
