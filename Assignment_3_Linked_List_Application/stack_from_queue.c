/*
 * This is the file in which you'll write the functions required to 
implement
 * a stack using two queues.  Make sure to add your name and 
@oregonstate.edu
 * email address below:
 *
 * Name:Meghan Dougherty 
 * Email:dougherm@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef TYPE
#define TYPE int
#endif

/**************************************************
 All of the initial Queue functions
 ***************************************************/
struct link {
	TYPE value;
	struct link * next;
};

struct listQueue {
	struct link *firstLink;
	struct link *lastLink;
	int size;
};

/*
* This function takes a queue and allocates the memory. It then
* creates a sentinel and assigns the first link and last link
* to the sentinel.
*/
void listQueueInit(struct listQueue *q) {
	
	//create the sentinel
	struct link* sentinel = malloc(sizeof(struct link));
	sentinel->next = NULL;
	
	//initialize the first and last links.
	q->firstLink = sentinel;
	q->lastLink = sentinel;
	q->firstLink->next = q->lastLink;
	

}

/*
 * This function creates a new queue. Parts of the create include 
allocating
 * the memory, initializing all of the values and returning a pointer to 
the newly
 * created queue.
 */
struct listQueue * listQueueCreate()
{
	//create a pointer to a new Queue;
	struct listQueue* newQueue = malloc(sizeof(struct listQueue));
		
	//initialize the new Queue;
	listQueueInit(newQueue);

	//set the newQueue size to 0;
	newQueue->size = 0;

	//return the pointer.
	return newQueue;
}


/*
* This function returns a 1 or 0 based on the statement looking at
* the first link. If the next value is null it is empty, and will return 1
*/
int listQueueIsEmpty(struct listQueue *q) {
	
	//return whether or not the size is 0;
	return q->size == 0;

}

/*
 * This function adds a new link and value to the back of the queue. It 
takes
 * a list and a type variable, allocates the memory and adjusts the proper 
links
 * to make the connection. No return value.
 */
void listQueueAddBack(struct listQueue *q, TYPE e) {
	
	//save the old last link
	struct link *oldLast = q->lastLink; //original final link
	
	//create and initialize the new last link
	q->lastLink = malloc(sizeof(struct link)); //create link to be added to back
	q->lastLink->value= e;
	q->lastLink->next = NULL;

	//add the new last link into the chain
	oldLast->next = q->lastLink;
	
	//increate the size.
	q->size++;
}

/*
 * This function takes a list argument and removes the link at the front.
 */
void listQueueRemoveFront(struct listQueue *q) {
	
	//make sure the list is not empty.
	assert(!listQueueIsEmpty(q));

	//Save the link to be removed
	struct link *front = q->firstLink->next;
	
	//close the gap 
	q->firstLink->next = front->next;

	//link the list to itself if the item removed is the only item in the stack.
	if (q->firstLink->next == 0)
	{
		q->lastLink = q->firstLink;
	}

	//free the link.
	free(front);
	
	q->size--;
}

/*
 * Function returns the value at the front of the list.
 */
TYPE listQueueFront(struct listQueue *q) {
	
	//return the value of the link after the sentinel.
	return (q->firstLink->next->value);

}


/*
* This function is a tester function that iterates through the list
* and prints out the values at each link.
*/
void printList(struct listQueue* l)
{
	assert(l != 0);
	
	struct link * printMe = l->firstLink->next;

	while (printMe!= NULL)
	{
		printf("Value: %d\n", printMe->value);
		printMe = printMe->next;
	}
}

/**************************************************
Stack Implementation
***************************************************/

struct linkedListStack {
	struct listQueue *Q1;
	struct listQueue *Q2;
	int structSize;
};

/*
 * This function initializes the values of the created Stack. Initializes 
both 
 * queues and the structSize.
 */
void linkedListStackInit(struct linkedListStack * s)
{
	//create and initialize the two queues.
	s->Q1 = listQueueCreate(s->Q1);
	s->Q2 = listQueueCreate(s->Q2);

	//set the size to 0;
	s->structSize = 0;
 }

/*
* This function creates the linked list stack. It allocates the memory and 
calls the
* initialization function to initialize all of the values. It then returns 
the stack.
*/
struct linkedListStack * linkedListStackCreate(){

	//create and initialize the stack.
	struct linkedListStack* s = malloc(sizeof(struct linkedListStack));

	linkedListStackInit(s);

	return s;
}

/*
* This function returns 1 if the linked list stack is empty and otherwise 
returns a 0.
*/
int linkedListStackIsEmpty(struct linkedListStack *s) {

	//return whether or not the struct size is 0;
	return (s->structSize == 0);

}

/*
 * This is the linked list acting as a stack push function. It takes 
 * a linked list stack argument and a value and pushes it onto the stack. 
The
 * funciton then also increases the size of the stack by 1. 
 */
void linkedListStackPush(struct linkedListStack *s, TYPE d) {

	//add the link and increase the struct size.
	listQueueAddBack(s->Q1, d);
	s->structSize++;


}
/*
 * This funciton pops a value off of the stack. It does this by moving all 
values
 * that are currently on the stack to the other queue. The stack top is 
maintained
 * at the back of the queue list. 
 */
void linkedListStackPop(struct linkedListStack *s) {
	
	//check if the stack is empty and print an error message if so.
	if (linkedListStackIsEmpty(s))
	{
		printf("The Stack is Empty!\n\n");
		
	}
	//Otherwise.
	else 
	{
		//Loop through the list, taking items from Q1 and moving them to Q2
		while (s->Q1->firstLink->next->next != NULL)
		{
			TYPE value = listQueueFront(s->Q1);
			listQueueRemoveFront(s->Q1);
			listQueueAddBack(s->Q2, value);
		}
		//remove the final link in Q1.
		listQueueRemoveFront(s->Q1);

		//Flip the Queues so that the values are in Q1.
		struct listQueue* temp = s->Q2;
		s->Q2 = s->Q1;
		s->Q1 = temp;

		//Decrease the struct size.
		s->structSize--;
	}
}
/*
 * This function returns the value that is at the back of the queue that is 
 * maintaing the values of the stack. 
 */
TYPE linkedListStackTop(struct linkedListStack *s) {
	
	//loop through the list moving items from Q1 to Q2.
	while (s->Q1->firstLink->next->next != NULL)
	{
		TYPE value = listQueueFront(s->Q1);
		listQueueRemoveFront(s->Q1);
		listQueueAddBack(s->Q2, value);
	}
	
	//Save the value of the last item in Q1
	TYPE top = listQueueFront(s->Q1);

	//Move the last item to Q2.
	listQueueRemoveFront(s->Q1);
	listQueueAddBack(s->Q2, top);

	//Flip the Queues so that Q1 has the values.
	struct listQueue* temp = s->Q2;
	s->Q2 = s->Q1;
	s->Q1 = temp;

	//return the saved value.
	return top;

}

/*
 * This function gores through the stack and removes each link in the 
queue.
 * It then frees the struct itself. 
 */
void linkedListStackFree(struct linkedListStack *s){
	
      assert(s != 0);
	
	while (s->structSize != 0) 
	{
		linkedListStackPop(s);
	}

	free(s->Q1->firstLink);
	free(s->Q2->firstLink);
	free(s->Q1);
	free(s->Q2);

	free(s);



}

/*
 * Main is used to test the stack ADT.
 */
int main(int argc, char* argv[])
{
	struct linkedListStack *stack = linkedListStackCreate();

	//Test Stack
	//Push 4 values onto the stack
	printf("Pushing the value: 1\n");
	linkedListStackPush(stack, 1);
	printf("Pushed.\n\n");

	printf("Pushing the value: 2\n");
	linkedListStackPush(stack, 2);
	printf("Pushed.\n\n");

	printf("Pushing the value: 3\n");
	linkedListStackPush(stack, 3);
	printf("Pushed.\n\n");

	printf("Pushing the value: 4\n");
	linkedListStackPush(stack, 4);
	printf("Pushed.\n\n");

	

	//Print value at the top and then remove it
	printf("Value at the top of stack %d now being popped. \n",linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");
	
	
	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");
	
	
	
	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));
	linkedListStackPop(stack);
	printf("Value popped.\n\n");

	
	
	printf("Value at the top of stack: %d now being popped. \n", linkedListStackTop(stack));  
	linkedListStackPop(stack);
	printf("Value popped.\n\n");
	
	
	//Try to pop when the stack is empty prints error:
	printf("Trying to pop empty stack:\n");

	linkedListStackPop(stack);

	
	//Push and Pop alternating
	printf("Pushing the value: 10\n");
	linkedListStackPush(stack, 10);
	printf("Pushed.\n\n");

	printf("Pushing the value: 11\n");
	linkedListStackPush(stack, 11);
	printf("Pushed.\n\n");
	
	printf("One more pop:\n");
	linkedListStackPop(stack);
	printf("Value at the top of stack: %d\n", 
	linkedListStackTop(stack));

	linkedListStackFree(stack);
	

	return 0;

}


