/***************
Tim Whitaker
***************/

#include "schedule.h"
#include <stdlib.h>

struct Node 
{
    int pid;
    int priority;
    struct Node *next;
    struct Node *previous;
};

struct Queue 
{
    int quanta;
    struct Node *front;
    struct Node *back;
    struct Node *current_node;
};

struct Queue* current_queue = NULL;

struct Queue *queue1 = (struct Queue*)malloc(sizeof(struct Queue));
queue1->quanta = 4;
queue1->front = NULL;
queue1->back = NULL;
queue1->current_node = NULL;
struct Queue *queue2 = (struct Queue*)malloc(sizeof(struct Queue));
queue2->quanta = 3;
queue2->front = NULL;
queue2->back = NULL;
queue2->current_node = NULL;
struct Queue *queue3 = (struct Queue*)malloc(sizeof(struct Queue));
queue3->quanta = 2;
queue3->front = NULL;
queue3->back = NULL;
queue3->current_node = NULL;
struct Queue *queue4 = (struct Queue*)malloc(sizeof(struct Queue));
queue4->quanta = 1;
queue4->front = NULL;
queue4->back = NULL;
queue4->current_node = NULL;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init(){

}

/**
 * Function to add a process to the scheduler
 * @Param pid - the ID for the process/thread to be added to the
 *      scheduler queue
 * @Param priority - priority of the process being added
 * @return true/false response for if the addition was successful
 */
int addProcess(int pid, int priority){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->pid = pid;
    temp->priority = priority;
    switch(priority)
    {
        case 1:
            if (queue1->front == NULL && queue1->back == NULL)
            {
                queue1->front = queue1->back = temp;
            }
            break;
        case 2:
            temp->quanta = 3;
            break;
        case 3: 
            temp->quanta = 2;
            break;
        case 4:
            temp->quanta = 1;
            break;
        default:
            return 0;
    }
    temp->next = NULL;
    temp->previous = NULL;
    
    if (hasProcess())
    {
        back->next = temp;
        temp->previous = back;
        back = temp;
    }
    else
    {
        front = back = temp;
    }
    return 1;
}

/**
 * Function to remove a process from the scheduler queue
 * @Param pid - the ID for the process/thread to be removed from the
 *      scheduler queue
 * @Return true/false response for if the removal was successful
 */
int removeProcess(int pid){
    if (!hasProcess()) return 0;
    else
    {
        struct Node *temp = front;
        while (temp->pid != pid)
        {
            if (temp->next == NULL) return 0;
            else temp = temp->next;
        }
        //only 1 node
        if (front == back)
        {
            front = back = NULL;
            free(temp);
            return 1;
        }
        //front node
        if (temp == front)
        {
            front = temp->next;
            front->previous = NULL;
            free(temp);
            return 1;
        }
        //back node
        if (temp == back)
        {
            back = temp->previous;
            back->next = NULL;
            free(temp);
            return 1;
        }
        //middle node
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
        free(temp);
    }
    return 1;
}
/**
 * Function to get the next process from the scheduler
 * @Param time - pass by pointer variable to store the quanta of time
 * 		the scheduled process should run for
 * @Return returns the thread id of the next process that should be
 *      executed, returns -1 if there are no processes
 */
int nextProcess(int *time){
    if (!hasProcess()) return -1;
    else
    {
        //getting process for first time
        if (current == NULL)
        {
            current = front;
            *time = current->quanta;
            return current->pid;
        }
        //back process
        if (current->next == NULL)
        {
            current = front;
            *time = current->quanta;
            return current->pid;
        }
        //everything else
        current = current->next;
        *time = current->quanta;
        return current->pid;
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
