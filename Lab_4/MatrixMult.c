
#include <stdio.h>
#include <stdlib.h>

int** createArray(int n) {
	int **arr = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			printf("Enter element [%d][%d]: ", i, j);
			scanf("%d", &(*(*(arr + i) + j)));
		}
	}
	return arr;
}
int** createArray_simple(int n) {
	int **arr = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++) {
		arr[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			(*(*(arr + i) + j)) = 0;
		}
	}
	return arr;
}
int** matMult(int **a, int **b, int size) {
	int **result = createArray_simple(size);
	// (4) Implement your matrix multiplication here. 
	// You will need to create a new matrix to store the product.
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			for(int k = 0; k < size; k++) {
				(*(*(result + i) + j)) += *(*(a + i) + k) * *(*(b + k) + j);
			}
		}
	}
	return result;
}

void printArray(int ** array, int size) {
    // (5) Implement your printArr here:
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			printf("%d ", *(*(array + i) + j));
		}
		printf("\n");
	}

}
int main() {
	int n = 0;
	int **matA, **matB, **matC;
	// (1) Define 2 (n x n) arrays (matrices). 
	printf("Enter size of matrices: ");
	scanf("%d", &n);
	matA = createArray(n);
	matB = createArray(n);

	// (3) Call printArray to print out the 2 arrays here.
	printArray(matA, n);
	printf("\n");
	printArray(matB, n);

	// (5) Call matMult to multiply the 2 arrays here.
	matC = matMult(matA, matB, n);
	printf("\n");	
	// (6) Call printArray to print out resulting array here.
	
	printArray(matC, n);

    return 0;
}