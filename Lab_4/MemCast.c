#include <stdio.h>

int main() {
	int i;
	int four_ints[4];
	char* four_c;

	for(i = 0; i < 4; i++)
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]);
	
    four_c = (char*)four_ints;

	for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // Add your code for the exercises here:
	for(i = 0; i < 4; i++)
		printf("%x ", four_c[i]);
	
	printf("%p\n", four_c);
	//00000092A75FF7B0
	//00000092A75FF7B0
	printf("%p\n", &four_ints);
	printf("\n");	
		
	// for ints
	printf("Ints:\n");
	for (i = 0; i < 4; i++)
	{
		printf("Value: %d\n", four_ints[i]);
		printf("Pointer: %p\n", &four_ints[i]);
		printf("Hex: %x\n", four_ints[i]);
		printf("\n");

	}
	printf("\n");
	for (i = 0; i < 4; i++)
	{
		printf("Value: %c\n", four_c[i]);
		printf("Pointer: %p\n", &four_c[i]);
		printf("Hex: %x\n", four_c[i]);
		printf("\n");
	}
	

	printf("\n");
	printf("%x", 15);
	return 0;
}