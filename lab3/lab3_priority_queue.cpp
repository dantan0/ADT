#include "lab3_priority_queue.hpp"
#include <iostream>

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    size = 0;
    capacity = n_capacity;
    heap = new TaskItem *[n_capacity+1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
    // traverse through the heap and delete each element in the array
    for (int i = 1; i < size; i++) {
        delete heap[i];
        heap[i] = NULL;
    }
    delete heap;
    heap = NULL;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size <= capacity ? size : capacity;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return (size == 0);
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return (size==capacity);
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    for (int i = 1; i <= size; i++) {
        cout << "-------------------" << endl;
        cout << "Element " << i << endl;
        cout << "Priority: " << heap[i] -> priority << endl;
        cout << "Description: " << heap[i] -> description <<endl;
    }
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (size == 0) { //if heap is empty
        return TaskItem(-1,"N/A");
    } else { // heap is the first element
        return *heap[1];
    }
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
    TaskItem *temp = new TaskItem (val.priority, val.description);

    if (size == capacity) {//base case: when the heap is full
        return false;
    } else if (size == 0) {//base case: when the heap is empty
        heap[1] = temp;
    } else { // use max heap
        int i = size + 1;
        heap[i] = temp;
        // if the parent node has a smaller value than the node
        // switch places with the parent
        while (i > 1 && heap[i/2] -> priority < heap[i] -> priority) {
            temp = heap[i/2];
            heap[i/2] = heap[i];
            heap[i] = temp;
            i /= 2;
        }
    }
    size ++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {

    if (size == 0) { // if heap is empty
        return false;
    }

    // replace the root node with the last node and remove the last node
    heap[1] = heap[size];
    delete heap[size];
    size--;

    // switch the new root node with the highest valued child and keep recursing downwards
    for (int i = 1; i <= size; i = i*2) {
        TaskItem *temp = heap[i];

        if (heap[i]->priority > heap[i*2]->priority && heap[i]->priority > heap[i*2+1]->priority) {
            // if the parent is greater than both children
            return true;
        } else if (heap[i*2]->priority > heap[i*2+1]->priority) {
            // if the left child is greater than the right child
            heap[i] = heap[i*2];
            heap[i*2] = temp;
        } else {
            // if the right child is greater than the left child
            heap[i] = heap[i*2+1];
            heap[i*2+1] = temp;
        }
    }
}