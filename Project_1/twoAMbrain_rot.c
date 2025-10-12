#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
    // Declaring Functions allow you to use them later in the code with have it be in sequential order. - Tabel
// Feel free to declare any helper functions or global variables

// ! Better Comments by Aaron Bond
// TODO: This needs fixing (orange)
// ! This is important (red)
// ? Should this be refactored? (blue)
// * Highlighted info (green)
// // Normal comment (gray)

void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
// * Helper functions
int compareLetters(char a, char b);
int **create_empty_array(int size);
void print_empty_array(int** arr, int size);
void get_firstLetter_BeginSearch(char** arr, char first_letter);
// Global variable for puzzle block size
int bSize;


// Define Node once and provide a typedef so 'Node' can be used directly
typedef struct Node {
    int row, col, increment;
    char letter;
    struct Node *next;
} Node;

Node *head;
int ** Path_Array; // Global variable for path array


// ! Main function, DO NOT MODIFY 	
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
// ! End of main function

//* Ma' Playground
// (Node is defined above with typedef)

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

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    struct Node *head = malloc(sizeof(struct Node));
    
    // Use path_array to mark first letter positions
    Path_Array = create_empty_array(bSize);
    get_firstLetter_BeginSearch(arr, *word);
    print_empty_array(Path_Array, bSize);

    // use linked list to search branching paths

    // Search in all 8 directions from each marked position - if letter matches, continue
    
    // // If full word is found, print success message
    
    // If found, mark the path in path_array

    // If full word found, update path_array to mark the path

    // if not found, print failure message and remove marks from path_array

    // print found or not found

    // Print results as path array
    
    // Free allocated memory


}



// Helper function to compare letters case insensitively
// this uses ASCII values to compare
// A-Z = 65-90
// a-z = 97-122
// difference is 32
int compareLetters(char a, char b) {
    if (a == b || a + 32 == b || a - 32 == b) {
        return 1;
    }
    return 0;
}

// creates an empty 2D array of size 'size' and initializes all elements to 0
// * sends back to global path_array
int **create_empty_array(int size) {
    
    int **result = (int**)malloc(size * sizeof(int*));
    // TODO: Dont forget to allocate memory for each row
    for (int i = 0; i < size; i++) {
        result[i] = malloc(size * sizeof(int));
    }
    // TODO --------------
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(result + i) + j) = 0;
        }
    }
    return result;
}

void print_empty_array(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%5d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

// checks how many times the first letter appears in the puzzle
void get_firstLetter_BeginSearch(char** arr, char first_letter) {
    int count = 0;
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (compareLetters(*(*(arr + i) + j), first_letter)) {
                *(*(Path_Array + i) + j) = -1; // mark the position in Path_Array
            }
        }
    }
}

// use a linked list to track the path of the search
// each node will store the row, col, increment (direction), and letter

// create a new node and return a pointer to it
Node* create_node(int row, int col, int increment, char letter) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->row = row;
    new_node->col = col;
    new_node->increment = increment;
    new_node->letter = letter;
    new_node->next = NULL;
    return new_node;
}

void search_array(char** arr, char* word) {
    // grab first marked position from path_array
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (*(*(Path_Array + i) + j) == -1) {
                // found a marked position
                // set head to that position
                head->row = i;
                head->col = j;
                head->letter = *(*(arr + i) + j);
                head->increment = 0;
                head->next = NULL;
            }
        }
    }
    // search in all 8 directions from that position for next letter

    // if found, create a new node and link it to the list

    
}
// placeholder: search in 8 directions — returns NULL for now
Node* search_8_directions(char** arr, char* word, int index, Node* current){
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if(i == (i+1) && j == (j+1)) {
                // down right
                
            }
            if(i == (i+1) && j == (j-1)) {
                // down left
            }
            if(i == (i-1) && j == (j+1)) {
                // up right
            }
            if(i == (i-1) && j == (j-1)) {
                // up left
            if(i == (i+1) && j == j) {
                // down
            }
            if(i == (i-1) && j == j) {
                // up
            }
            if(i == i && j == (j+1)) {
                // right
            }
            if(i == i && j == (j-1)) {
                // left
            }
            else {
                // out of bounds
            }
        }
    }
    return NULL;
}
