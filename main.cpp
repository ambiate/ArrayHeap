/*
* file: driver-proj5.cpp
* author: Jonathan Drouillard
* course: CSI 3334
* assignment: Project 5
* due date: Friday, 11/11/2011, 11:59:59PM
* version: 1
* 
* This file contains the driver for the Project and ArrayHeap class.
*/

#include "process-proj5.h"
#include "arrayheap-student-proj5.h"
#include <iostream>

using namespace std;

int main() {
    int id = 0, skipped = 0, systemTime = 0, numProcs = 0, ticks = 0, nextTicks;
    
    cin >> numProcs;
    bool firstRun = true;
    ArrayHeap<Process> heap;

    cin >> ticks;
    nextTicks = ticks;

    while(id < numProcs || heap.getNumItems() != 0) {
        cout << "current time is " << systemTime << ", the number of runnable processes is " << heap.getNumItems() << endl;
        Process current(id);
        if(id < numProcs) {
            ticks = nextTicks;
            cin >> current;
        
            if(systemTime < ticks && heap.getNumItems() == 0) {
                cout << "moving the clock forward to " << ticks << " ticks since there are no processes to run" << endl;
                systemTime = ticks;
             }
            cout << "[1]a new process has started at time " << ticks << "; we will give it id " << id << " and put it on the heap" << endl;
            int old = nextTicks;
            heap.insert(current);
            cin >> nextTicks;
            if(nextTicks > systemTime) {
                if(heap.getMinItem().canComplete(systemTime)) {
                    cout << "[running process id " << heap.getMinItem().getId() << " at " << systemTime << endl;
                    systemTime = heap.getMinItem().run(systemTime);
                    heap.removeMinItem();
                }
                else if(!heap.getMinItem().canComplete(systemTime)) {
                    cout << "skipping process id " << heap.getMinItem().getId() << " at " << systemTime << endl;
                    systemTime++;
                    skipped++;
                    heap.removeMinItem();
                }
            }
            bool done2 = false;
            int nextID2 = id+1;
            while(!done2 && (nextID2 < numProcs)) {
                if(nextTicks <= systemTime) {
                    Process next2(nextID2);
                    cin >> next2;
                    cout << "a new process has started at time " << nextTicks << "; we will give it id " << nextID2 << " and put it on the heap" << endl;
                    heap.insert(next2);
                    id = nextID2;
                    nextID2++;
                    ticks = old;
                    old = nextTicks;
                    cin >> nextTicks;
                }
                else {
                    done2 = true;
                    if(heap.getNumItems() != 0) {
                        if(heap.getMinItem().canComplete(systemTime)) {
                            cout << "running process id " << heap.getMinItem().getId() << " at " << systemTime << endl;
                            systemTime = heap.getMinItem().run(systemTime);
                            heap.removeMinItem();
                            if(nextTicks <= systemTime) {
                                done2 = false;
                            }
                        }
                        else if(!heap.getMinItem().canComplete(systemTime)) {
                            cout << "skipping process id " << heap.getMinItem().getId() << " at " << systemTime << endl;
                            systemTime++;
                            skipped++;
                            heap.removeMinItem();
                            if(nextTicks <= systemTime) {
                                done2 = false;
                            }
                        }
                    }
                }
            }
            
        }

        id++;
    }

    cout << "final clock is                 " << systemTime << endl
         << "number of processes run is     " << abs(numProcs-skipped) << endl
         << "number of processes skipped is " << skipped << endl;

    return 0;
}