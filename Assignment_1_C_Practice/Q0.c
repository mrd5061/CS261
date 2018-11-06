/* CS261- Assignment 1 - Q. 0*/
/* Name: Meghan Dougherty
 * Date: 10/09/2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*fooA: takes one integer pointer as an argument. Prints the value the pointer
 * points too and the address of the variable the pointer points too. Then,
 * increments the the value of the variable the pointer points to by 5. Then,
 * prints the address of the function pointer.  *
 * */
void fooA(int* iptr){
  
     /*Print the value and address of the integer pointed to by iptr*/
	printf("The value pointed to by iptr is:  %d \n", *iptr);
	printf("The address of the variable pointed to by iptr is %p \n", iptr);
     /*Increment the value of the integer pointed to by iptr by 5*/
	*iptr += 5;
     /*Print the address of iptr itself*/
	printf("The address of iptr is: %p \n \n", &iptr);
}


/*fooB: takes one integer pointer as an argument. Prints the value of  and 
 * address of the variable pointed to by the function pointer. Then, decreases
 * the value of the variable pointed to. Then, prints the address of the 
 * function pointer.
 * */

void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
	printf("The value pointed to by jptr is: %d \n", *jptr);
	printf("The address of the variable pointed to by jptr is: %p \n", jptr);
     /*Decrement jptr by 1*/
	*jptr -= 1;
     /*Print the address of jptr itself*/
	
	printf("The address of jptr is: %p \n \n", &jptr);
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] 
*/
	int x = 2;
    
    /*Print the value and address of x*/
	printf("The value of x is: %d \n", x);
	printf("The address of x is: %p \n \n", &x);
    /*Call fooA() with the address of x*/
	fooA(&x);
    /*Print the value of x*/
	printf("The value of x is: %d \n \n", x);
	//The value of x is different because fooA function incremented the value of x via iptr. 

    /*Call fooB() with the address of x*/
	fooB(&x);
    /*Print the value and address of x*/
	printf("The value of x is: %d \n", x);
	printf("The address of x is: %p \n \n", &x);

	/*The address of x is still the same because it's a static variable and it's address will 
	remain the same until the program ends. 
	The value of x is different because the fooB decrememented the value of x via jptr. 
	*/
	

    return 0;
}


