#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	list->frontSentinel = (struct Link *) malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);

	list->backSentinel = (struct Link *) malloc(sizeof(struct Link));
	assert(list->backSentinel);

	list->frontSentinel->next = list->backSentinel;
	list->frontSentinel->prev = NULL;

	list->backSentinel->prev = list->frontSentinel;
	list->backSentinel->next = NULL;

	list->size = 0;

}
/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);

	//create the new link and assert it's creation.
	struct Link* newLink = (struct Link*) malloc(sizeof(struct Link));

	assert(newLink != 0);

	//set the new link's value;
	newLink->value = value;

	//set the new link's prev to the old link's prev and the new link's next to the old link,
	newLink->prev = link->prev;
	newLink->next = link;

	//set the old link's prev to the new link.
	link->prev->next = newLink;
	link->prev = newLink;

	(list->size)++; 
	
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(list != NULL);

	//assign the previous link's next pointer to the deleted link's next.
	link->prev->next = link->next;

	//assign the next link's previous pointer to the deleted link's previous.
	link->next->prev = link->prev;

	//delete the link.
	free(link);
	
	//decrease the size.
	list->size--;

}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	//make sure the list isn't empty.
	assert(list != NULL);

	//utilize the addLinkBefore function, providing the link after the front sentinel.
	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	//make sure the list isn't empty
	assert(list != NULL);

	//utilize the addLinkBefore function, providing the back sentinel.
	addLinkBefore(list, list->backSentinel, value);

}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != NULL);
	return list->frontSentinel->next->value;
}


/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != NULL);
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != NULL);

	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != NULL);

	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	return (list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != NULL);

	struct Link* incLink = list->frontSentinel->next;

	while (incLink != list->backSentinel) {
		
		printf( "%i ", incLink->value);
		incLink = incLink->next;
	}
	printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	//make sure the list isn't empty.
	assert(list != NULL);
	
	//add the link to the front of the bag.
	linkedListAddFront(list, value);

	
	
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	//make sure the list isn't empty.
	assert(list != NULL);

	//set the bool variable to 0 (false).
	int containsVal = 0;

	//create a pointer for checking the links.
	struct Link* incLink = list->frontSentinel->next;

	//while loop to cycle through the list.
	while (incLink != list->backSentinel && containsVal == 0) {
		if (incLink->value == value) {
			containsVal = 1;
		}
		incLink = incLink->next;
	}

	//return the result.
	return containsVal;

}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);

	struct Link* incLink = list->frontSentinel->next;

	while (incLink != list->backSentinel) {
		if (incLink->value == value) {
			removeLink(list, incLink);
			return;
		}
		incLink = incLink->next;
	}

}
