#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	//Allocate the memory
	list->sentinel = (struct Link *) malloc(sizeof(struct Link));

	//check the allocation	
	assert(list->sentinel != 0);

	//Make the sentinel point to itself.
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	//initialize the size.
	list->size = 0;

}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link* newLink = malloc(sizeof(struct Link));
	newLink->next = NULL;
	newLink->prev = NULL;
	newLink->value = value;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);

	struct Link* newLink = createLink(value);

	//add the link into the chain.
	newLink->next = link->next;
	newLink->prev = link;

	//set the pointers for the links surrounding the added link.
	newLink->next->prev = newLink;
	newLink->prev->next = newLink;
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	//make sure the list isn't empty.
	assert (!circularListIsEmpty(list));

	//remove the link from the chain
	link->prev->next = link->next;
	link->next->prev = link->prev;

	//delete the link
	free(link);

	//decrement the size
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	//allocate memory for the list
	struct CircularList* list = malloc(sizeof(struct CircularList));

	//initialize the list.
	init(list);

	//return the list
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	//add a link after the sentinel.
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	//add a link before the sentinel.
	addLinkAfter(list, list->sentinel->prev, value);
	
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert (!circularListIsEmpty(list));

	//return the value of the link in front of the sentinel.
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));

	//return the value of the link before the sentinel.
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));

	//remove the link after the sentinel.
	removeLink(list, list->sentinel->next);
}
/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(!circularListIsEmpty(list));

	//remove the link before the sentinel.
	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	return (list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	//create a pointer to traverse the list
	struct Link* incLink = list->sentinel->next;

	//traverse the list, printing the value and incrementing the pointer.
	while (incLink != (list->sentinel))
	{
		printf("%g ", incLink->value);
		incLink = incLink->next;
	}
	//print a newline character for formatting purposes.
	printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	//create a pointer to traverse the list.
	struct Link * incLink = list->sentinel;

	//traverse the list.
	for (int i = 0; i < list->size + 1; i++) {
		
		//temp pointer to store the current link's next value..
		struct Link * temp = incLink->next;

		//make the current link's next point to the previous link.
		incLink->next = incLink->prev;

		//make the current link's previous point to the old value of the current link's next.
		incLink->prev = temp;
		
		//increase the traversal pointer.
		incLink = incLink->next;
	}
}
