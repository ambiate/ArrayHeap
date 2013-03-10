/*
* file: arrayheap-student-proj5.cpp
* author: Jonathan Drouillard
* course: CSI 3334
* assignment: Project 5
* due date: Friday, 11/11/2011, 11:59:59PM
* version: 1
* 
* This file contains the implementation of the ArrayHeap class.
*/

#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>
#include <cassert>
using namespace std;


//MileStone I
//bubbleUp, and bubbleDown.

/*
* ArrayHeap Default Constructor
*
* This function is the constructor for a templated ArrayHeap object
*
* Parameters: None.
*
* Return value: None.
*/
template <class Base>
ArrayHeap<Base>::ArrayHeap() {
    capacity = 10;
    numItems = 0;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];
    for(int i = 0; i < capacity; i++) {
        heapAndFreeStack[i] = i;
    }
}

/*
* ArrayHeap Copy Constructor
*
* This function is the copy constructor for a templated ArrayHeap object
*
* Parameters: A templated ArrayHeap item.
*
* Return value: None.
*/
template <class Base>
ArrayHeap<Base>::ArrayHeap(const ArrayHeap<Base> &h) {
    numItems = h.numItems;
    capacity = h.capacity;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];
    for(int i = 0; i < numItems; i++) {
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}

/*
* ArrayHeap Destructor
*
* This function is the destructor for a templated ArrayHeap object
*
* Parameters: None.
*
* Return value: None.
*/
template <class Base>
ArrayHeap<Base>::~ArrayHeap() {
    if(data) {
        delete [] data;
    }
    if(heapAndFreeStack) {
        delete [] heapAndFreeStack;
    }
    numItems = 0;
    capacity = 0;
}

/*
* ArrayHeap operator=
*
* This function is the makes the current ArrayHeap object equivalent to the passed in object.
*
* Parameters: The templated ArrayHeap object to copy.
*
* Return value: The given ArrayHeap object to permit equality chaining (no combo points).
*/
template <class Base>
const ArrayHeap<Base> &ArrayHeap<Base>::operator=(const ArrayHeap<Base> &ah) {

    if(this == &ah) {
        return *this;
    }

    if(data) {
        delete [] data;
    }
    if(heapAndFreeStack) {
        delete [] heapAndFreeStack;
    }
    numItems = ah.numItems;
    capacity = ah.capacity;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];
    for(int i = 0; i < capacity; i++) {
        data[i] = ah.data[i];
        heapAndFreeStack[i] = ah.heapAndFreeStack[i];
    }
}

/*
* insert
*
* This function inserts an item into the heap, and then it restores
* the heap order property by bubbling the item up.
*
* Parameters: Item to insert into the heap.
*
* Return value: None.
*/
template <class Base>
void ArrayHeap<Base>::insert(const Base &item) {
    if(numItems == capacity) {
        doubleCapacity();
    }
    data[heapAndFreeStack[numItems]] = item;
    
    //cout << "UP UP UP" << endl;
    bubbleUp(numItems);
    
    numItems++;
    
    if(numItems > 1) {
        bubbleDown(0);
    }
    /*cout << "inserting, new list is: " << endl;
    for(int i = 0; i < numItems; i++) {
        cout << heapAndFreeStack[i] << " : " << data[heapAndFreeStack[i]].getId() << endl;
    }



    cout << "----" << endl;
    */
    
    
}

/*
* removeMinItem
*
* This function removes the root item from the arrayheap,
* places in the last element from level order traversal,
* and performs a bubble down on the new root.
*
* Parameters: Location in the array to begin the bubbleUp.
*
* Return value: None.
*/
template <class Base>
void ArrayHeap<Base>::removeMinItem() {
    if(numItems == 0) {
        assert(false);
    }
    //cout << "DOWN DOWN DOWN" << endl;
    //cout << data[heapAndFreeStack[0]].getId() << endl;
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems-1]);
    numItems--;
    //cout << data[heapAndFreeStack[0]].getId() << endl;
    if(numItems > 0)// {
        bubbleDown(0);
    //bubbleUp(numItems-1);
    //}
    /*cout << data[heapAndFreeStack[0]].getId() << endl;
        cout << "removing, new list is: " << endl;
    for(int i = 0; i < numItems; i++) {
        cout << "h&fs[" << i << "] " << heapAndFreeStack[i] << endl;
        cout << "id for data[hfs[" << i << "]]" << data[heapAndFreeStack[i]].getId() << endl;
    }
    cout << "----" << endl;
    */
}

/*
* getMinItem
*
* This function returns the minimum item at the top of the heap.
*
* Parameters: None.
*
* Return value: The value stored the top of the heap.
*/
template <class Base>
const Base &ArrayHeap<Base>::getMinItem() const {
    return data[heapAndFreeStack[0]];
}

/*
* getNumItems
*
* This function returns the number of items in the heap.
*
* Parameters: None.
*
* Return value: The number of items stored in the heap.
*/
template <class Base>
int ArrayHeap<Base>::getNumItems() const {
    return numItems;
}

/*
* doubleCapacity
*
* This function doubles the capacity of the data and heapAndFreeStack data members.
*
* Parameters: None.
*
* Return value: None.
*/
template <class Base>
void ArrayHeap<Base>::doubleCapacity() {
    Base *tmpData = new Base[capacity*2];
    int *tmpHandFS = new int[capacity*2];

    for(int i = 0; i < capacity; i++) {
        tmpData[i] = data[i];
        tmpHandFS[i] = heapAndFreeStack[i];
    }

    capacity*=2;
    delete [] data;
    delete [] heapAndFreeStack;
    data = tmpData;
    heapAndFreeStack = tmpHandFS;
}

/*
* bubbleUp
*
* This function moves an item up the heap to correct heap order property.
*
* Parameters: Location in the array to begin the bubbleUp.
*
* Return value: None.
*/
template <class Base>
void ArrayHeap<Base>::bubbleUp(int ndx) {
    int parent = (heapAndFreeStack[ndx-1])/2;
    //cout << "parent is" << parent << endl;
    if(parent < 1) { //at root
        return;
    }
    if(data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]) {
        //cout << "Swapping " << data[heapAndFreeStack[ndx]].getId() << " AND " << data[heapAndFreeStack[parent]].getId() << endl;
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);
        bubbleUp(parent);
    }
}

/*
* bubbleDown
*
* This function moves an item up the heap to correct heap order property.
*
* Parameters: Location in the array to begin the bubbleDown.
*
* Return value: None.
*/
template <class Base>
void ArrayHeap<Base>::bubbleDown(int ndx) {
    int child = 2*ndx+1;

    if (2*ndx+1 > numItems-1)
        return;
    
    if (child+1 < numItems && data[heapAndFreeStack[child+1]] < data[heapAndFreeStack[child]])
        child++;

    if (data[heapAndFreeStack[child]] < data[heapAndFreeStack[ndx]])
    {
        swap(heapAndFreeStack[ndx], heapAndFreeStack[child]);
        bubbleDown(child);
    }
}


#endif

