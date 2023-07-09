#include "Heap.h"
#include "PrintJob.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Initializes an empty heap
Heap::Heap() {
    numItems = 0;
}

// Inserts a printjob to the heap without violating max heap properties
void Heap::enqueue(PrintJob* job) {
    if (numItems >= MAX_HEAP_SIZE) { // Array is FULL, so output error
        cout << "Job queue is full. Cannot Enqueue" << endl;
        return;
    }
    else { // array has room

        // Insert the new job at the end of the array
        arr[numItems] = job;
        trickleUp(numItems);
        numItems++; // Increment number of items in the heap
    }
}

// Removes the node with highest priority from the heap. 
void Heap::dequeue() {
    if (numItems == 0) {
        cout << "Heap empty, cannot dequeue" << endl;
        return;
    }

    else if (numItems == 1) { // heap has one node
        arr[0] = 0;
        numItems = 0;
        return;
    }

    else { // Heap has at least 1 node 
        arr[0] = arr[numItems - 1]; // Set root, or the first node in the heap, to the last node in the heap

        numItems--; // Decrement number of items in the heap

        trickleDown(0); // Move new root node back into correct position
    }
}

// Returns the node with highest priority.
PrintJob* Heap::highest() {
    if (numItems == 0) {
        cout << "Heap empty, cannot find highest priority node" << endl;
        return 0;
    }

    else { // Otherwise if heap is not empty, return the first (root) node which has the highest priority
        return (arr[0]);
    }
}

// Prints the PrintJob with highest priority in the following format: Priority: priority, Job Number: jobNum, Number of Pages: numPages \n
void Heap::print() {
    if (numItems == 0) {
        cout << "Heap empty, nothing to print out" << endl;
        return;
    }

    else { // Heap is not empty, print out the highest priority node
        PrintJob *PriorityNode = highest();

        cout << "Priority: " << PriorityNode->getPriority() << ", ";
        cout << "Job Number: " << PriorityNode->getJobNumber() <<  ", ";
        cout << "Number of Pages: " << PriorityNode->getPages() << endl; 
    }
}

// Called by enqueue function to sort the heap back to its max heap
void Heap::trickleUp(int index) {
    if (index == 0) {
        return; // Already at root, don't need to do anything
    }

    else {
        while(index >= 1 && arr[index]->getPriority() > arr[(index - 2)/2]->getPriority()) {
            swap(arr[index], arr[(index - 1)/2]); // Moving up the heap; sort the heap back to max heap using swap
            index = (index - 1) / 2;
        }
    }
}

// This function is called by dequeue function to move the new root down the heap to the appropriate location.
void Heap::trickleDown(int index) {
    if (index > 3) {
        return;
    }

    // Get the index of left and right child
    int leftChild = (2 * index) + 1;
    int rightChild = (2 * index) + 2;

    // If number of items in the heap is greater than left and right child index, compare priority of parent node with left and right child
    if (numItems > leftChild && numItems > rightChild) {
        // Priority of the parent node is less than its children -> swap parent node with the child that has a higher priority
        if (arr[index]->getPriority() < arr[leftChild]->getPriority() || arr[index]->getPriority() < arr[rightChild]->getPriority()) {
            // Left child has higher priority than right and parent. Swap parent index with left child index, then trickle down on left child
            if (arr[leftChild]->getPriority() > arr[rightChild]->getPriority()) {
                swap(arr[index],arr[leftChild]);
                trickleDown(leftChild);
            }
            // Otherwise, swap parent index with right child index, then trickle down on right child
            else {
                swap(arr[index],arr[rightChild]);
                trickleDown(rightChild);
            }
        }
    }
    // If the number of items is greater than leftChild index but not right, simply swap parent with right child
    else if (numItems > leftChild) {
        swap(arr[index],arr[rightChild]);
    }
}
