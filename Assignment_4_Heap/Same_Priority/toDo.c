/*
 * CS 261 Assignment 4
 * Name: Meghan Dougherty
 * Date: 11/19/2018
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    int timeStamp = 0;
    Task temp; 
    while(fscanf(file, format, &temp.priority, &temp.name) ==2)
    {
	dyHeapAdd(heap, taskNew(temp.priority, temp.name, timeStamp), taskCompare);
        timeStamp++;
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command,int timeStamp)
{
	//Create variables for the file name, name of the task, and the tasks' priority.
	char* file = malloc(sizeof(256));
	char* name = malloc(sizeof(256));
	char opt;
	int priority;

	switch(command){
	case 'l':

		printf("If you load a file, your current list will be lost. Continue y/n? \n");
		opt = getchar();

		if(opt =='n' || opt == 'N')
		{
			while((getchar())!='\n');
			break;
		}
		while((getchar()) != '\n');
		printf("Please enter the name of the file you want to load.\n");
		fgets(file, 100, stdin);

		//remove trailing newline
		if (file[strlen(file) - 1] == '\n')
			file[strlen(file) - 1] = 0;

		FILE* fileOpen = fopen(file, "r");
		if (fileOpen == NULL)
		{
			printf("Cannot open %s \n", file);
			break;
		}
		dyDelete(list);
		list = dyNew(8);

		listLoad(list, fileOpen);
		fclose(fileOpen);
		
		printf("Successfully opened %s \n", file);
		break;
	case 's':
		printf("Please enter the name of the file you want to save.\n");
		fgets(file, 100, stdin);

		//remove trailing newline
		if (file[strlen(file) - 1] == '\n')
			file[strlen(file) - 1] = 0;

		FILE* fileWrite = fopen(file, "w");

		if (fileWrite == NULL)
		{
			printf("Cannot open %s \n", file);
			break;
		}

		listSave(list, fileWrite);
		fclose(fileWrite);
		printf("Successfully saved %s \n", file);
		break;

	case 'a':
		printf("Please enter the name of your task \n");
		fgets(name, 100, stdin);
		if (name[strlen(name) - 1] == '\n')
			name[strlen(name) - 1] = 0;
		do{
		printf("Please enter the priority of your task \n");
		scanf("%d", &priority);
		}while(priority <0 || priority > 999);

		Task *task = taskNew(priority, name, timeStamp);
		dyHeapAdd(list, task, taskCompare);
		printf("The task '%s' has been added to the list.\n", name);
		
		while((getchar()) != '\n');
		break;

	case 'g':
		if (dySize(list) != 0)
			printf("Your first task is: %s\n", ((struct Task*)dyHeapGetMin(list))->name);
		else
			printf("Your list is empty!\n");
		break;
	case 'r':
		if(dySize(list)==0){
			printf("Your list is empty!\n");
			break;
		}
		else {
			struct Task* t = (struct Task*) dyHeapGetMin(list);
			dyHeapRemoveMin(list, taskCompare);
			printf("Your task %s has been removed \n", t->name);
			taskDelete(t);
			break;
		}
		
	case 'p':
		if (dySize(list) == 0){
			printf("Your list is empty!\n");
			break;}
		else {
			listPrint(list);
			break;
		}
		
	case 'e':
		printf("Goodbye!\n");
		break;
	}
	free(file);
	free(name);
	 

}

int main()
{
    int timeStamp = 0;
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command, timeStamp);
        timeStamp++;
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
