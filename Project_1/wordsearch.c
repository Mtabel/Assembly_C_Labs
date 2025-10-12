#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);

// * Helper functions
int compareLetters(char a, char b);
int **create_empty_array(int size);
void ** mark_possible_start(char **arr, int size, char first_letter, int **Path_Array);
void print_int_array(int** arr, int size);



int bSize;

int **Possible_Paths; // Global variable for path array


// ! Better Comments by Aaron Bond
// TODO: This needs fixing (orange)
// ! This is important (red)
// ? Should this be refactored? (blue)
// * Highlighted info (green)


// !--------------------------------------------------------------
// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

// !--------------------------------------------------------------

// Completed
void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i)+ j));
        }
        printf("\n");
    }

}


// TODO: Master Function; to be implemented
void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    // Make empty path array
    Possible_Paths = create_empty_array(bSize);
    
    // mark possible starting positions
    mark_possible_start(arr, bSize, *word, Possible_Paths);
    // print
    print_int_array(Possible_Paths, bSize);









    // TODO: Pseudocode
    // Find First Occurrence of First Letter : can be done with a nested loop
    // ? if found call to Traverse() function
    // if no first letter found, print not found message -- Easiest case

    
    // Traverse(char** arr, char* word, int row, int columb) VVV
    // * Nested loop to find/use first letter -- Needs to give all attempts a chance
        //Create a linked list to store the path of the word found - starting from the first letter found


        // Check all 8 directions from the first letter found
        // if next letter in sequence is found, traverse in that direction
        // if next letter is not found, mark as bad path and backtrack and try another direction


        // if sequence is found, send to helper array function for printing

        // -------------------------------
    //if word single instance found, print word found message
    //else print not found message
}

// allows case insensitive comparison of letters due to aSCII values
int compareLetters(char a, char b) {
    if (a == b || a + 32 == b || a - 32 == b) {
        return 1;
    }
    return 0;
}


int **create_empty_array(int size) {
    int **result = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        *(result + i) = malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(result + i) + j) = 0;
        }
    }
    return result;
}
void ** mark_possible_start(char **arr, int size, char first_letter, int **Path_Array) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (compareLetters(*(*(arr + i) + j), first_letter)) {
                *(*(Path_Array + i) + j) = -1; // mark the position in Path_Array
            }
        }
    }
}
void print_int_array(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%5d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}
