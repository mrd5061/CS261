/* CS261- Assignment 1 - Q.3*/
/* Name: Meghan Dougherty 
 * Date:
 * Description:  takes a string where words are separated by underscores. 
 * The string  is first converted by removing and non alpha an non underscore 
 * characters
 * and converting all alpha characters to lowercase. Camelcase then converts
 * the string by removing any underscores and capitalizing the character 
 * immediately following any underscores. 
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>

/*toUpperCase: takes a character variable as an argument. returns that 
 * character in it's upper case form. It is assumed that the passed
 * character is lower case alphabetic. 
 * */

char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
	return ch - 32; 
}

/*toLowerCase: takes a character variable as an argument. Returns that
 * character in it's lower case form. It is assumed that the passed character
 * is upper case alphabetic. 
 * */

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
	return ch + 32;
}

/*stringLenght: takes a string as an array of characters as an argument.
 * returns the length of the passed string. 
 * */

int stringLength(char s[]) {
   /*Return the length of the string*/
	int count= 0;

	for (int i = 0; s[i] != '\0'; ++i)
	{
		++count;
	}

	return count;
}

/*camelCase: takes a character pointer to a string. Converts the string by
 * removing an extant underscores and capitalizing the character immediately
 * following any underscores.*/

void camelCase(char* word)
{
	/*Convert to camelCase*/
	int length = stringLength(word);

	//If a character is an underscore. If so, remove underscore and capitaliz the following character.
	for (int i = 0; i < length; i++)
	{
		if (word[i] == '_')
		{					
			for (int j = i; j < length; j++)
			{
				word[j] = word[j + 1];
			}
			word[i] = toUpperCase(word[i]);
		}
	}
		
}

int main(){
	//initialize necessary variables
	char word[255];
	int j; //used as an index for various for loops
	int counter = 0;

	/*Read the string from the keyboard. Will accept white space.*/
	
	printf("Please enter a string to convert. \n");
	scanf("%[^\n]s", word);

	int length = stringLength(word);

	/*Verify Correct input and convert*/
	
	//Verify that there are some alpha characters
	for (int i = 0; i <= length; i++)
	{
		
		if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
		{
			++counter;
		}

	}

	//If no alpha characters exist, print error and exit. 
	if (counter == 0)
	{
		printf("Invalid input string \n");

		
		return 0;
	}

	//Convert input for camel case.
	for (int i = 0; i <= length; i++)
	{
		
		//remove non alpha non underscore characters
		while (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == '\0' || word[i] == '_'))
		{
			for (j = i; j <= length; j++)
			{
				if (j == length)
					word[j] = '\0';
				else
					word[j] = word[j + 1];
			}

		}
		
		//de-capitalize as needed.
		while (!((word[i] >= 'a' && word[i] <= 'z')||word[i]=='\0'||word[i]=='_'))
		{
			word[i] = toLowerCase(word[i]);
		}

		//Check for double underscores.
		while ((word[i] == '_'&& word[i + 1] == '_' &&word[i]!='\0'))
		{
			for (j = i; j <= length; j++)
			{
				if (j == length)
					word[j] = '\0';
				else
					word[j] = word[j + 1];
			}
		}

		

	
	}
	//Replace any white space with underscores
	for(int i=0; i<length; i++)
	{
		if(word[i] == ' ')
			word[i] = '_';
	}

	//Remove leading underscore if extant.
	if (word[0] == '_')
	{
		for (int i = 0; i <= length; i++)
		{
			word[i] = word[i + 1];
		}
	}

	//Remove trailing underscore if extant.
	if(word[stringLength(word)-1] == '_')
	{
		for (int i = stringLength(word) - 1; i <= stringLength(word); i++)
		{
			word[i] = word[i + 1];
		}
	}

	/*Call camelCase*/

	camelCase(word);

	
	/*Print the new string*/
	printf("%s \n", word);
	
	
	return 0;
}

