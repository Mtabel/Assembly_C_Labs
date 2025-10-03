#include <stdio.h>
#include <stdlib.h>

 int main() {
	int num;
	int *ptr;
	int **handle;

	num = 14;
	ptr = (int *) malloc(2 * sizeof(int));
	*ptr = num;
	handle = (int **) malloc(1 * sizeof(int *)); // allocate space for a single int pointer - Note sizeof(int*)
	*handle = ptr;

	// Insert code here
	printf("memory address of num: %p\n", (void*)&num);
	printf("Value of num: %d\n", num);
	printf("\n");
	printf("Address of ptr: %p\n", ptr);
	printf("Address of handle: %p\n", handle);
	printf("\n");
	printf("Value pointed to by ptr: %d\n", *ptr);
	printf("Value pointed to by handle: %d\n", **handle);	//Sweet.
	return 0;
} 

