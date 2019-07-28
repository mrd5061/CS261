/*
 * CS 261 Assignment 4
 * Name: Meghan Dougherty
 * Date: 11/19/2018
 * IMPORTANT NOTE: I adjusted the definition of the task struct in the header. This file will not work with the skeleton
   file provided with the assignment brief. 
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name, int timeStamp)
{
	struct Task* newTask = malloc(sizeof(struct Task));

	strcpy(newTask->name, name);
	newTask->priority = priority;
        newTask->timeStamp = timeStamp;
	return newTask;
    
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
	
	struct Task* leftT = (struct Task*) left;
	struct Task* rightT = (struct Task*) right;
	
		if (leftT->priority < rightT->priority)
			return -1;
		else if (leftT->priority > rightT->priority)
			return 1;
		else if (leftT->priority == rightT->priority)
		{
			if(leftT->timeStamp < rightT->timeStamp)
				return -1;
			else if(leftT->timeStamp > rightT->timeStamp)
				return 1;
		}
		else
			return 0;
	
   
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("%d, %s", task->priority, task->name);
}
