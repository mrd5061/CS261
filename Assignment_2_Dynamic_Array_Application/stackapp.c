/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	if (s == NULL)
	{
		return 1;
	}
	DynArr* stack = newDynArr(25);
	char next = nextChar(s);
	while(next !='\0')
	{
		if (next == '{' || next == '(' || next == '[')
			pushDynArr(stack, next);
		else if (next == '}' || next == ')' || next == ']')
		{
			if (stack == NULL)
				return 0;
			
			popDynArr(stack);
		}
		next = nextChar(s);
		
	}
	
	if (isEmptyDynArr(stack))
	{	
		freeDynArr(stack);
		return 1;
	}
	else
	{
		freeDynArr(stack);
		return 0;
	}
	
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];
	int res;
	
	printf("Assignment 2\n");
	
	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	
	return 0;	
}

