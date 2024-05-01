#include <stdio.h>

int main()
{
	int x = 10;
	/*
		here the value 10 is stored in the variable x . Actually it is 
		stored at a location in the memory.
	*/

	/*
		in order to get the address of the location im memory where the x value 10 is stored.
		we use a pointer to store the address
	*/
	int *pointerForX = &x;
	
	printf("\nVariable X address : %p -> %d",&x, *(&x));
	printf("\nValue stored in the pointer : %p -> %d",pointerForX,*pointerForX);
	printf("\nAddress of the pointer variable : %p\n", &pointerForX);

    pointerForX = &pointerForX;

    printf("\nPointer to pointer : %p", pointerForX);
    printf("\nPOinter value : %p", &pointerForX);
    printf("\nvalue at pointer address : %d", *pointerForX);

	return 0;
}