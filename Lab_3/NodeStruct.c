#include <stdio.h>
#include <stdlib.h>

struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {

    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;
	
	// Insert code here
    printf("Node address: %p\n", head);
	printf("Node integer value: %d\n", head->iValue);
    printf("Node float value: %f\n", head->fValue);
    printf("Node next pointer value: %p\n", head->next);
	
	return 0;
}