/*
 * CS 261 Data Structures
 * Assignment 5
 * Name:Meghan Dougherty 
 * Date: 11/25/2018
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}


/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
	struct HashLink* itr = map->table[0];
	struct HashLink* temp;
	for (int i = 0; i < map->capacity; i++)
	{
		while (itr != NULL)
		{
			temp = itr;
			itr = itr->next;
			hashLinkDelete(temp);
		}

		
	}
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	int index = HASH_FUNCTION(key) % hashMapCapacity(map);

	struct HashLink* itr = map->table[index];

	while (itr != NULL)
	{
		if (strcmp(itr->key, key) == 0)
		{
			return &(itr->value);
		}

		itr = itr->next;
	}

    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	struct HashLink* itr = NULL;
	struct HashMap* temp = hashMapNew(capacity);

	for (int i = 0; i < hashMapCapacity(map); i++)
	{
		itr = map->table[i];

		while (itr != NULL)
		{
			hashMapPut(temp, itr->key, itr->value);
			itr = itr->next;
		}
	}

	hashMapCleanUp(map);
	map->size = temp->size;
	map->table = temp->table;
	map->capacity = temp->capacity;
	free(temp);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	// FIXME: implement
	float factor;
	int capacity = hashMapCapacity(map);
	int idx = HASH_FUNCTION(key) % capacity;

	if (idx < 0) 
	{
		idx += capacity;
	}

	if (hashMapContainsKey(map, key)) 
	{
		int* val = hashMapGet(map, key);
		(*val) += value;
	}
	else {
		HashLink* newLink = hashLinkNew(key, value, NULL);

		assert(newLink != NULL);

		if (map->table[idx] == NULL)
		{
			map->table[idx] = newLink;
		}
		else
		{
			HashLink* itr = map->table[idx];
			while (itr->next) {
				itr = itr->next;
			}
			itr->next = newLink;
		}
		map->size++;
	}

	factor = hashMapTableLoad(map);

	if (factor >= MAX_TABLE_LOAD) {
		resizeTable(map, 2 * capacity);
	}


}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
	assert(map != NULL);
	assert(key != NULL);

	int idx = HASH_FUNCTION(key) % hashMapCapacity(map);
	HashLink* itr = map->table[idx];
	HashLink* preItr = NULL;

	if (itr != NULL) {
		if (strcmp(itr->key, key) == 0)
		{
			map->table[idx] = itr->next;
		}
		else 
		{
			while (strcmp(itr->key, key) != 0) 
			{
				preItr = itr;
				itr = itr->next;
			}

			if (preItr)
			{
				preItr->next = itr->next;
			}
		}

		hashLinkDelete(itr);
		map->size--;
	}
	
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
	// FIXME: implement
	assert(map != NULL);
	assert(key != NULL);

	int cap = hashMapCapacity(map);
	int idx = HASH_FUNCTION(key) % cap;

	if (idx < 0) {
		idx += cap;
	}

	HashLink* cur = map->table[idx];

	while (cur) {
		if (strcmp(cur->key, key) == 0) {
			return 1;
		}
		cur = cur->next;
	}

	return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int total=0; 
	

	for (int i=0; i < hashMapCapacity(map); i++)
	{
		if (map->table[i] == NULL)
		{
			total++;
		}
	}
    return total;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	float size = (float)hashMapSize(map);
	float capacity = (float)hashMapCapacity(map);
    return size/capacity;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
	for (int i=0; i < hashMapCapacity(map); i++)
	{
		struct HashLink* itr = map->table[i];

		if (itr != NULL)
		{
			printf("\n Bucket %i->", i);
			while (itr != NULL)
			{
				printf("(%s, %d)->", itr->key, itr->value);
				itr = itr->next;
			}
			
		}
   }

   
}
