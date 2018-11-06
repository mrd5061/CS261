/* CS261- Assignment 1 - Q.1*/
/* Name: Meghan Dougherty
 * Date: 10/07/2018
 * Solution description: These functions randomly generate id numbers and 
 * test scores for 10 students, prints the data, and  calculates the minimum
 * maximum and average scores. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

/*allocate: takes no arguments. creates an array of 10 stutend structs. 
 * returns the pointer to the array. 
 * */
struct student* allocate(){
     /*Allocate memory for ten students*/
	

	struct student* myStudents = malloc(10 * sizeof(struct student));

	/*Return the pointer*/

	return myStudents;
    
}

/*generate: takes one student struct pointer as an argument. Generates random
 * ID's (# between 1 and 10 inclusive) and random scores (# between 0 and 100
 * inclusive) and assigns the random numbers to the ten students assicated
 * with the struct array. Utilizes the Fisher Yates shuffle. 
 * */

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/

// create local variables to hold values for shuffle
	int i = 0;
	int j = 0;
	int tmp; 
//First Array for the ID Fisher Yates Shuffle.
	int array1[10] = { 1,2,3,4,5,6,7,8,9,10};

//Second Array for the Score Fisher Yates Shuffle.
	int array2[100]; 

	//initialize the array. 
	for (int x = 0; x < 99; x++)
	{
		array2[x] = x;
	}

//Fisher Yates Shuffle to generate Random IDS.
	for (i = 9; i > 0; i--)
	{
		j = rand() % 10;
		tmp = array1[j];
		array1[j] = array1[i];
		array1[i] = tmp;
	}

//Assign the IDS
	for (i = 0; i < 10; i++)
	{
		students[i].id = array1[i];
	}

//Fisher Yates Shuffle to generate random scores.
	for (i = 99; i > 0; i--)
	{
		j = rand() % 100;
		tmp = array2[j];
		array2[j] = array2[i];
		array2[i] = tmp;
	}
//Assign the scores. 
	for (i = 0; i < 10; i++)
	{
		students[i].score = array2[i+1];
	}
}

/*output: takes one student struct pointer as an argument. Prints the ids
 * and the scores of the ten associated students. 
 * */

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/

	for (int i = 0; i < 10; i++)
	{
		printf(" %d, %d \n \n", students[i].id, students[i].score);
		
	}
}

/* summary: takes one student struct pointer as an argument. Computes, then
 * prints the minimum, maximum, and average scores of the students assicated
 * with the passed student array. 
 * */

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
     
	//Initialize the local variables. 
	int minScore = students[0].score;
	int maxScore = students[0].score;
	int average = 0;

	for (int i = 0; i < 10; i++)
	{
		/*Compare the current student's score to the minimum and maximum. 
		Set the current student's score to those variables if either condition
		is met.*/

		if (students[i].score < minScore)
			minScore = students[i].score;
		if (students[i].score > maxScore)
			maxScore = students[i].score;

		//Add the student's score to the average. 
		average += students[i].score;
	}

	//Calculate the average score. 
	average /= 10;

	//Print the results. 
	printf("The minimum score is: %d \n", minScore);
	printf("The maximum score is: %d \n", maxScore);
	printf("The average score is: %d \n \n", average);
}

/*deallocate: takes one student struct pointer as an argument. Frees any
 * dynamically allocated memory associated with said pointer. 
 * */

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);
}

int main(){
	
   struct student* stud = NULL;
    
    /*Call allocate*/
	stud = allocate();

    /*Call generate*/
	generate(stud);

    /*Call output*/
	output(stud);

    /*Call summary*/
	summary(stud);

    /*Call deallocate*/
	deallocate(stud);


	return 0;
}

