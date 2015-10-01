/*************
Tim Whitaker
*************/

#include "schedule.h"
#include <stdlib.h>

struct Node 
{
    int pid;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *back = NULL;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init(){
}

/**
 * Function to add a process to the scheduler
 * @Param pid - the ID for the process/thread to be added to the
 *      scheduler queue
 * @return true/false response for if the addition was successful
 */
int addProcess(int pid){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->pid = pid;
    temp->next = NULL;
    
    if (hasProcess())
    {
        back->next = temp;
        back = temp;
    }
    else
    {
        front = back = temp;
    }
    
    return 0;
}

/**
 * Function to get the next process from the scheduler
 *
 * @Return returns the thread id of the next process that should be
 *      executed, returns -1 if there are no processes
 */
int nextProcess(){
    if (!hasProcess())
    {    
        return -1;
    }
    else
    {
        int pid;
        struct Node *temp = front;
        if (front == back)
        {
            pid = front->pid;
            front = back = NULL;
        }
        else
        {
            pid = front->pid;
            front = front->next;
        }
        free(temp);
        return pid;
    }
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
    return (front == NULL && back == NULL) ? 0 : 1;
}
