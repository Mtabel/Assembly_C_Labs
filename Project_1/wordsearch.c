#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CustomLinkedList.h"

/*
    Created by Matthew Tabel, Dina Seoudi.
    10/13/25
*/

#define DEBUG 0 // 0 = off, 1 = on

// ---- Globals ----
int bSize;
int global_breakout = 1; // Breakout variable not activated
int iteration = 1;       // Iteration counter for debugging

int **Possible_Paths; // Global variable for path array
int **attemps_grid;   // Grid to track attempts
LinkedList* list;

// ---- Declarations ----
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);

// * Helper functions
int compareLetters(char a, char b);
int **create_empty_array(int size);
void mark_possible_start(char **arr, int size, char first_letter, int **Path_Array);
void print_int_array(int** arr, int size);
int search_from_position(char** arr, char* word, int row, int col);
void mark_path(int** Path_Array, LinkedList* list);
void pretty_print_path(int** Possible_Paths, LinkedList* list);
int return_hights_place(int number); // returns the highest place value of a number
int return_number_readyToPaste(int number_to_add, int number);

// bonus helpers
typedef struct {
    LinkedList **items;
    int count;
    int cap;
} PathBag;

void paths_init(PathBag *b, int cap) {
    b->items = (LinkedList**)malloc(cap * sizeof(LinkedList*));
    b->count = 0;
    b->cap   = cap;
}

void copy_list_into(LinkedList *dst, LinkedList *src, char *word) {
    Node *t = src->head;
    while (t != NULL) {
        append(dst, t->valid_path, t->row, t->col, word);
        t = t->next;
    }
}

void paths_add(PathBag *b, LinkedList *src, char *word) {
    if (b->count == b->cap) {
        b->cap = (b->cap == 0 ? 1 : b->cap * 2);
        b->items = (LinkedList**)realloc(b->items, b->cap * sizeof(LinkedList*));
    }
    LinkedList *copy = createList();
    copy_list_into(copy, src, word);
    *(b->items + b->count) = copy;
    b->count += 1;
}

void paths_free(PathBag *b) {
    for (int i = 0; i < b->count; ++i) {
        freeList(*(b->items + i));
    }
    free(b->items);
}

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
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

// allows case insensitive comparison of letters due to ASCII values
int compareLetters(char a, char b) {
    if (a == b || a + 32 == b || a - 32 == b) {
        return 1;
    }
    return 0;
}

// Helper function to create an empty 2D integer array
int **create_empty_array(int size) {
    int **result = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        *(result + i) = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(result + i) + j) = 0;
        }
    }
    return result;
}

void mark_possible_start(char **arr, int size, char first_letter, int **Path_Array) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (compareLetters(*(*(arr + i) + j), first_letter)) {
                *(*(Path_Array + i) + j) = -999; // mark the position in Path_Array
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


// Search in all 8 directions from the given position
int search_from_position(char** arr, char* word, int row, int col) {
    for(int k = 0; k < 3; k++) {
        for(int l = 0; l < 3; l++) {
            if(k == 1 && l == 1) {
                continue; // Skip the center position (0,0)
            }
            // Offsets for 3x3 grid -- handled by nested loops
            int newRow = row + (k - 1);
            int newCol = col + (l - 1);
            // Check bounds and if the next letter matches
            if(newRow >= 0 && newRow < bSize && newCol >= 0 && newCol < bSize &&
               compareLetters(*(*(arr + newRow) + newCol), *(word + get_list_length(list))) &&
               (get_last_node(list)->increment + 1) != -*(*(Possible_Paths + newRow) + newCol) &&
               *(*(attemps_grid + newRow) + newCol) < 3) {
                append(list, 1, newRow, newCol, word);
                return 1; // Found and appended
            }
        }
    }
    return 0; // Not found in any direction
}

void mark_path(int** Path_Array, LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        *(*(Path_Array + temp->row) + temp->col) = temp->increment; // Mark the path
        if(DEBUG == 1) {
            printf("Marking path at (%d,%d) with %d\n", temp->row, temp->col, temp->increment);
        }
        temp = temp->next;
    }
}

// number concat helpers
int return_hights_place(int number) {
    int result = 0;
    while (number > 0) {
        number /= 10;
        result++;
    }
    return result;
}
int return_number_readyToPaste(int number_to_add, int number) {
    int highest_place = return_hights_place(number_to_add); // make space for the new number
    int result = 0;
    for (int i = 0; i < highest_place; i++) {
        number *= 10;
    }
    result += number_to_add;
    result += number;
    return result;
}

// Pretty Path Printing (single path)
void pretty_print_path(int** Path_Array, LinkedList* pathList) {
    Path_Array = create_empty_array(bSize); // Reset for final path

    // Properly format the path numbers
    Node* temp = pathList->head;
    while (temp != NULL) {
        // fixed precedence: dereference full cell value first
        if (*(*(Path_Array + temp->row) + temp->col) > 0) {
            *(*(Path_Array + temp->row) + temp->col) =
                return_number_readyToPaste(*(*(Path_Array + temp->row) + temp->col), temp->increment);
        } else {
            *(*(Path_Array + temp->row) + temp->col) = temp->increment; // Mark the path as normal if not
        }
        if(DEBUG == 1) {
            printf("Marking path at (%d,%d) with %d\n", temp->row, temp->col, temp->increment);
        }
        temp = temp->next;
    }

    print_int_array(Path_Array, bSize);

    // free the created matrix
    for (int r = 0; r < bSize; ++r) free(*(Path_Array + r));
    free(Path_Array);
}

// bonus: print all distinct-start paths
void searchPuzzle(char** arr, char* word) {
    Possible_Paths = create_empty_array(bSize);
    attemps_grid   = create_empty_array(bSize);
    mark_possible_start(arr, bSize, *word, Possible_Paths);

    PathBag results;
    paths_init(&results, bSize * bSize > 0 ? bSize * bSize : 1);

    for (int i = 0; i < bSize; ++i) {
        for (int j = 0; j < bSize; ++j) {
            if (*(*(Possible_Paths + i) + j) != -999) continue;

            for (int r = 0; r < bSize; ++r)
                for (int c = 0; c < bSize; ++c)
                    *(*(attemps_grid + r) + c) = 0;

            list = createList();
            append(list, 1, i, j, word);
            global_breakout = 1;

            while (global_breakout == 1 && get_list_length(list) < (int)strlen(word)) {
                int sr = get_last_node(list)->row;
                int sc = get_last_node(list)->col;

                global_breakout = search_from_position(arr, word, sr, sc);

                if (global_breakout == 0) {
                    (*(*(attemps_grid + sr) + sc))++;
                    *(*(Possible_Paths + sr) + sc) = -get_last_node(list)->increment;
                    remove_last(list);
                    global_breakout = (list->head != NULL) ? 1 : 0;
                }

                if (list->head == NULL) break;

                if (get_list_length(list) == (int)strlen(word)) {
                    paths_add(&results, list, word);
                    break;
                }
            }

            freeList(list);
            list = NULL;
        }
    }

    if (results.count > 0) {
        printf("Word found!\n");
        printf("Printing the search path:\n");
        for (int k = 0; k < results.count; ++k) {
            int **tmp = NULL;
            pretty_print_path(tmp, *(results.items + k));
            if (k < results.count - 1) printf("\n");
        }
        paths_free(&results);
    } else {
        printf("Word not found!\n");
        paths_free(&results);
    }

    for (int r = 0; r < bSize; ++r) free(*(Possible_Paths + r));
    free(Possible_Paths);
    for (int r = 0; r < bSize; ++r) free(*(attemps_grid + r));
    free(attemps_grid);
}
