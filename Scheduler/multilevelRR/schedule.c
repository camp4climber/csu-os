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
    struct Queue *next_queue;
    struct Node *front;
    struct Node *back;
};

struct Queue *current_queue = NULL;
struct Queue *queue1 = NULL;
struct Queue *queue2 = NULL;
struct Queue *queue3 = NULL;
struct Queue *queue4 = NULL;

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
    temp->next = NULL;
    temp->previous = NULL;
    switch(priority)
    {
        case 1:
            if (queue1 == NULL)
            {
                queue1 = (struct Queue*)malloc(sizeof(struct Queue));
                queue1->quanta = 4;
                queue1->front = NULL;
                queue1->back = NULL;
            }
            if (queue1->front == NULL && queue1->back == NULL)
            {
                queue1->front = queue1->back = temp;
            }
            else
            {
                queue1->back->next = temp;
                temp->previous = queue1->back;
                queue1->back = temp;
            }
            return 1;
        case 2:
            if (queue2 == NULL)
            {
                queue2 = (struct Queue*)malloc(sizeof(struct Queue));
                queue2->quanta = 3;
                queue2->front = NULL;
                queue2->back = NULL;
            }
            if (queue2->front == NULL && queue2->back == NULL)
            {
                queue2->front = queue2->back = temp;
            }
            else
            {
                queue2->back->next = temp;
                temp->previous = queue2->back;
                queue2->back = temp;
            }
            return 1;
        case 3: 
            if (queue3 == NULL)
            {
                queue3 = (struct Queue*)malloc(sizeof(struct Queue));
                queue3->quanta = 2;
                queue3->front = NULL;
                queue3->back = NULL;
            }
            if (queue3->front == NULL && queue3->back == NULL)
            {
                queue3->front = queue3->back = temp;
            }
            else
            {
                queue3->back->next = temp;
                temp->previous = queue3->back;
                queue3->back = temp;
            }
            return 1;
        case 4:
            if (queue4 == NULL)
            {
                queue4 = (struct Queue*)malloc(sizeof(struct Queue));
                queue4->quanta = 1;
                queue4->front = NULL;
                queue4->back = NULL;
            }
            if (queue4->front == NULL && queue4->back == NULL)
            {
                queue4->front = queue4->back = temp;
            }
            else
            {
                queue4->back->next = temp;
                temp->previous = queue4->back;
                queue4->back = temp;
            }
            return 1;
        default:
            return 0;
    }
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
        struct Queue *temp_queue; 

        if (queue1->front != NULL) temp_queue = queue1; 
        else if (queue2->front != NULL) temp_queue = queue2;
        else if (queue3->front != NULL) temp_queue = queue3;
        else temp_queue = queue4;

        struct Node *temp = temp_queue->front;
        while (temp->pid != pid)
        {
            if (temp->next == NULL && temp_queue == queue1) 
            {
                if (queue2->front != NULL) temp_queue = queue2;
                else if (queue3->front != NULL) temp_queue = queue3;
                else if (queue4->front != NULL) temp_queue = queue4;
                else return 0;
               
                temp = temp_queue->front;
            }
            else if (temp->next == NULL && temp_queue == queue2)
            {
                if (queue3->front != NULL) temp_queue = queue3;
                else if (queue4->front != NULL) temp_queue = queue4;
                else return 0;
                
                temp = temp_queue->front;
            }
            else if (temp->next == NULL && temp_queue == queue3)
            {
                if (queue4->front != NULL) temp_queue = queue4;
                else return 0;
                
                temp = temp_queue->front;
            }
            else if (temp->next == NULL && temp_queue == queue4)
            {
                return 0;
            }
            else temp = temp->next;
        }
        //only 1 node
        if (temp_queue->front == temp_queue->back)
        {
            temp_queue->front = temp_queue->back = NULL;
            free(temp);
            return 1;
        }
        //front node
        if (temp == temp_queue->front)
        {
            temp_queue->front = temp->next;
            temp_queue->front->previous = NULL;
            free(temp);
            return 1;
        }
        //back node
        if (temp == temp_queue->back)
        {
            temp_queue->back = temp->previous;
            temp_queue->back->next = NULL;
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
        if (current_queue == NULL)
        {
            if (queue1->front != NULL) current_queue = queue1;
            else if (queue2->front != NULL) current_queue = queue2;
            else if (queue3->front != NULL) current_queue = queue3;
            else if (queue4->front != NULL) current_queue = queue4;
        }
        else if (current_queue == queue1)
        {
            if (queue2->front != NULL) current_queue = queue2;
            else if (queue3->front != NULL) current_queue = queue3;
            else if (queue4->front != NULL) current_queue = queue4;
            else if (queue1->front != NULL) current_queue = queue1;
        }
        else if (current_queue == queue2)
        {
            if (queue3->front != NULL) current_queue = queue3;
            else if (queue4->front != NULL) current_queue = queue4;
            else if (queue1->front != NULL) current_queue = queue1;
            else if (queue2->front != NULL) current_queue = queue2;
        }
        else if (current_queue == queue3)
        {
            if (queue4->front != NULL) current_queue = queue4;
            else if (queue1->front != NULL) current_queue = queue1;
            else if (queue2->front != NULL) current_queue = queue2;
            else if (queue3->front != NULL) current_queue = queue3;
        }
        else if (current_queue == queue4)
        {
            if (queue1->front != NULL) current_queue = queue1;
            else if (queue2->front != NULL) current_queue = queue2;
            else if (queue3->front != NULL) current_queue = queue3;
            else if (queue4->front != NULL) current_queue = queue4;
        }
        *time = current_queue->quanta;
        int pid = current_queue->front->pid;
        int priority = current_queue->front->priority;
        removeProcess(pid);
        addProcess(pid, priority);
        return pid;
    }
    return -1;
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
    return (queue1->front == NULL && queue1->back == NULL &&
            queue2->front == NULL && queue2->back == NULL &&
            queue3->front == NULL && queue3->back == NULL &&
            queue4->front == NULL && queue4->back == NULL) 
            ? 0 : 1;
}
