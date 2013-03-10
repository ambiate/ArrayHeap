/*
* file: process-proj5.cpp
* author: Jonathan Drouillard
* course: CSI 3334
* assignment: Project 5
* due date: Friday, 11/11/2011, 11:59:59PM
* version: 1
* 
* This file contains the implementation of the Process class.
*/

#include "process-proj5.h"

/*
* Process constructor
*
* This function is a constructor for a Process object.
*
* Parameters: An Id to associate the process with that defaults to 0.
*
* Return value: None.
*/
Process::Process(int theId) {
    id = theId;
    deadline = 0;
    requiredTime = 0;
    information = "";
}

/*
* run
*
* This function prints out information about the process and the new system time.
*
* Parameters: The current system time as an integer.
*
* Return value: The current system time plus the time this process took to complete.
*/
int Process::run(int currentSystemTime) const {
    cout << information << endl;
    return currentSystemTime + requiredTime;
}

/*
* canComplete
*
* This function returns true if the process can complete by its deadline.
* The function will return false if it could not finish by its deadline.
*
* Parameters: The current system time as an integer.
*
* Return value: True if it can finish by its deadline, otherwise, false.
*/
bool Process::canComplete(int currentSystemTime) const {
    if(requiredTime + currentSystemTime <= deadline) {
        return true;
    }
    return false;
}

/*
* getId
*
* This function returns the Id of a Process Object.
*
* Parameters: None.
*
* Return value: The Id of this Process Object.
*/
int Process::getId() const {
    /*cout << "id: " << id << endl 
         << "deadline: " << deadline << endl
         << "required: " << requiredTime << endl
         << "infor   : " << information << endl;*/
    return id;
}

/*
* operator<
*
* This function moves an item up the heap to correct heap order property.
* It begins by testing deadlines.  If deadlines are equivalent, it tests required
* time.  If required times are also equivalent, the function tests by id.
*
* Parameters: A process to compare the < comparison on.
*
* Return value: True if the current process is < the passed in Process object.
*               False if the current process is > the passed in Process object.
*/
bool Process::operator<(const Process &p) const {
    if(deadline < p.deadline) {
        return true;
    }
    else if(p.deadline < deadline) {
        return false;
    }
    else {
        if(requiredTime < p.requiredTime) {
            return true;
        }
        else if(p.requiredTime < requiredTime) {
            return false;
        }
        else {
            if(id < p.id) {
                return true;
            }
            else if(p.id < id) {
                return false;
            }
            else {
                return false;
            }
        }
    }
}

/*
* operator>>
*
* This function allows a Process object to be streamed out.
*
* Parameters:
*  is: The stream which will send data to the Process object.
*   p: The object which will receive the data.
*
* Return value: The given stream to permit input chaining.
*/
istream &operator>>(istream &is, Process &p) {
    is >> p.deadline;
    is >> p.requiredTime;
    //works for succession and single line input.
    is.ignore(1); //ignore space if exists.
    getline(is, p.information);
    return is;
}

