/* CS261- Assignment 1 - Q.2*/
/* Name: Meghan Dougherty
 * Date: 10/07/2018
 * Solution description: Uses three variables with random values (0-10). Passes
 * those variables as pointers, swaps a two of the pointer addresses around,
 * and decrements the value of the third around before re-printing the 
 * variable values.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*foo: takes two pointers to int variables and one integer by reference. swaps
 * the address of pointer a and b. Also decrements C by one and returns the 
 * new value. 
 * */
int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
	int* temp;
	temp = a;
	a = b;
	b = temp;

    /*Decrement the value of integer variable c*/
	c--;
	/*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int x = rand() % 10;
	int y = rand() % 10;
	int z = rand() % 10;


    /*Print the values of x, y and z*/
	printf("The value of x is: %d \n", x);
	printf("The value of y is: %d \n", y);
	printf("The value of z is: %d \n", z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
	
	int q = foo(&x, &y, z);

    /*Print the values of x, y and z*/
	printf("The value of x is: %d \n", x);
	printf("The value of y is: %d \n", y);
	printf("The value of z is: %d \n", z);
    /*Print the value returned by foo*/
	printf("The value returned by foo is: %d \n", q);
	
	/*The vaule return value is different that the value of z because the function
	foo does not augment the variable z contents, only the value of z that is passed
	to the function. You would have to pass z as a pointer and then de-reference that
	pointer to make z and the return value the same. 

	The value of x and y are the same as before foo because x and y are static values
	not pointers. Furthermore, a and b are local variables. If we were to print the 
	values stored in a and b in foo, then we would see the values of x and y flip. 


	*/

    return 0;
}
    
    


