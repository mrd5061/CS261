#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    	char* word =  nextWord(file);
	while (word != NULL)
	{
		hashMapPut(map, word, 1);
		free(word);
		word = nextWord(file);
	}	
	free(word);

}
//Recursive function that suggests words that are close (levenshtein wise) to the misspelled word
void _suggestWords(HashMap* map, HashMap* wordMap, char* inputBuffer, int cap, int counter)

{	
		
	struct HashLink* itr;	
	//Search the whole of the dictionary
	for(int i = 0; i < hashMapCapacity(map); i++)
	{
				
		itr = map->table[i];
		
		while (itr && counter <5 )
		{
			//calculate the distance
			int dist = _levenshteinDist(inputBuffer, itr->key);

			//If the distance is less than the cap and the word is not already in the map, add it to the map.
			if(dist <= cap && !(hashMapContainsKey(wordMap, itr->key)))
			{
				hashMapPut(wordMap, itr->key,itr->value);
				counter ++;
			}
			itr= itr->next;
			
		}
		
	}
	//If we've gotten through the map and haven't found five words, increase the cap by one and search again.
	if(counter <5)
	{
		_suggestWords(map,wordMap, inputBuffer, cap + 1, counter);
		
	}	

	
}

//Levenshtein distance calculator that uses a matrix. 
//Source code heavily borrowed from https://www.lemoda.net/c/levenshtein/
int _levenshteinDist(char* word1, char* word2)
{
	int len1 = strlen(word1);
	int len2 = strlen(word2);
	int matrix[len1+1][len2+1];
	int i; 	
	for (i = 0; i<= len1; i++)
	{ matrix[i][0] = i;}
	for(i = 0; i<=len2; i++)
	{matrix[0][i] = i;}
	for(i=1; i<=len1; i++)
	{
		int j;
		char c1;
		c1  = word1[i-1];
		for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}
int _inputVal(char* string)
{
	for(int i = 0; i < strlen(string); i++)
	{
		if(!isalpha(string[i])|| isspace(string[i]))
			return 0;
	}
	return 1;

}
/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    struct HashMap* map = hashMapNew(1000);
    printf("Opening the dictionary.");
    FILE* file = fopen("dictionary.txt", "r");
    
    clock_t timer = clock();
   loadDictionary(file, map);

	
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
   
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word (only a-z or A-Z no spaces) or \"quit\" to quit: ");
        scanf("%[^\n]", inputBuffer);
        

        //Fix me:  implement the spell checker code here..
       while(! (_inputVal(inputBuffer)))
	  {
		  while((getchar())!= '\n');
		  printf("Invalid Input. Enter a word (only a-z or A-Z no spaces) or \"quit\" to quit: ");
        	scanf("%[^\n]", inputBuffer);
	  }
	
	if(strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }

	else if(hashMapContainsKey(map, inputBuffer))
	{
		printf("The word is spelled correctly \n");
	}
	else
	{
		HashMap* wordMap = hashMapNew(5);
		int cap = 1;
		printf("That word is spelled incorrectly. Did you mean: \n");
		_suggestWords(map,wordMap, inputBuffer, cap, 0);
		for(int i=0; i<hashMapCapacity(wordMap);i++)
		{
			struct HashLink* itr = wordMap->table[i];

			while (itr != NULL)
			{
				printf("%s \n", itr->key);
				itr = itr->next;
			}
			
		

  	 	}	
		hashMapDelete(wordMap);
	}	
     	while((getchar()) != '\n');      
    }    
    hashMapDelete(map);

    return 0;
}
