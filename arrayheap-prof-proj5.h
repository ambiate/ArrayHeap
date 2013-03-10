#ifndef ARRAY_HEAP_PROJ5_PROF_H
#define ARRAY_HEAP_PROJ5_PROF_H

/* 
 * The insert method inserts the given item into the heap (at the bottom),
 * and then restores the heap order property by bubbling the item up.
 *
 * The bubbleUp method can be implemented iteratively or recursively. It
 * starts at the item given by ndx, and moves it up the heap towards the
 * root in order to preserve the heap order property.
 *
 * The bubbleDown method can be implemented iteratively or recursively. It
 * starts at the item given by ndx, and moves it down the heap towards the
 * leaves in order to preserve the heap order property.
 *
 * The data member "data" contains the items that are stored in the heap.
 * Once an item is placed in data, it should not move.
 *
 * The data member "heapAndFreeStack" describes the structure of the heap (in
 * heapAndFreeStack[0] through heapAndFreeStack[numItems-1]), and it has a stack
 * of the indexes in data that are not being used (in heapAndFreeStack[numItems]
 * through heapAndFreeStack[capacity-1]).  Every value in this array (whether in
 * the heap or stack region) is an index into the array "data".
 *
 * The data member "numItems" contains the number of items on the heap, and
 * serves as the dividing line between the heap structure and the stack of free
 * items.
 *
 * The data member "capacity" represents the number of items that the heap can
 * contain before requiring extra space. The data and heapAndFreeStack arrays
 * both are capacity long.
 */
template <class Base>
class ArrayHeap {
    public:
        ArrayHeap();
        ArrayHeap(const ArrayHeap<Base> &h);
        ~ArrayHeap();

        const ArrayHeap<Base> &operator=(const ArrayHeap<Base> &ah);

        void insert(const Base &item);
        void removeMinItem();
        const Base &getMinItem() const;
        int getNumItems() const;
        void test() {
            for(int i = 0; i < numItems; i++) {
                cout << heapAndFreeStack[i] << endl;
                //cout << data[heapAndFreeStack[i]]. << endl;
                cout << data[heapAndFreeStack[i]].getId() << endl;
            }
        }

    private:
        Base *data;
        int *heapAndFreeStack;

        int numItems;
        int capacity;

        void doubleCapacity();
        void bubbleUp(int ndx);
        void bubbleDown(int ndx);
};

#endif

