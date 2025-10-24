#include <stdio.h>            // printf, scanf, FILE, fopen, etc.
#include <stdlib.h>           // malloc, free, realloc, NULL
#include <string.h>           // strlen, strcmp, etc.
#include "CustomLinkedList.h" // Node/LinkedList APIs: createList, append, get_last_node, remove_last, etc.

/*
    Created by Matthew Tabel, Dina Seoudi.
    10/13/25
*/

#define DEBUG 0 // 0 = off, 1 = on                              // debug printing toggle

// ---- Globals ----
int bSize;                                                         // puzzle/grid dimension (bSize x bSize)
int global_breakout = 1; // Breakout variable not activated       // controls stepping during search loop
int iteration = 1;       // Iteration counter for debugging        // not used here, reserved for debug

int **Possible_Paths; // Global variable for path array            // matrix: marks starts, visits, backtrack marks
int **attemps_grid;   // Grid to track attempts                    // matrix: counts attempts per cell
LinkedList* list;     // current path list (sequence of nodes)     // global pointer to active path

// ---- Declarations ----
void printPuzzle(char** arr);                                      // prints the char grid
void searchPuzzle(char** arr, char* word);                         // searches for word in grid

// * Helper functions
int compareLetters(char a, char b);                                // case-insensitive char compare
int **create_empty_array(int size);                                // allocates size x size int matrix, zeroed
void mark_possible_start(char **arr, int size, char first_letter, int **Path_Array); // mark cells matching first letter
void print_int_array(int** arr, int size);                         // prints int matrix (formatted)
int search_from_position(char** arr, char* word, int row, int col);// tries to extend path from (row,col)
void mark_path(int** Path_Array, LinkedList* list);                // writes path increments into matrix
void pretty_print_path(int** Possible_Paths, LinkedList* list);    // prints one path nicely (concats)
int return_hights_place(int number); // returns the highest place value of a number // digits count helper
int return_number_readyToPaste(int number_to_add, int number);     // concatenates digits (e.g., 24 + 6 -> 246)

// bonus helpers
typedef struct {
    LinkedList **items;                                            // dynamic array of found path lists
    int count;                                                     // number of stored paths
    int cap;                                                       // capacity of items
} PathBag;

void paths_init(PathBag *b, int cap) {
    b->items = (LinkedList**)malloc(cap * sizeof(LinkedList*));    // allocate items array
    b->count = 0;                                                  // start empty
    b->cap   = cap;                                                // set initial capacity
}

void copy_list_into(LinkedList *dst, LinkedList *src, char *word) {
    Node *t = src->head;                                           // iterate through src nodes
    while (t != NULL) {
        append(dst, t->valid_path, t->row, t->col, word);          // duplicate node fields into dst
        t = t->next;
    }
}

void paths_add(PathBag *b, LinkedList *src, char *word) {
    if (b->count == b->cap) {                                      // grow array when full
        b->cap = (b->cap == 0 ? 1 : b->cap * 2);
        b->items = (LinkedList**)realloc(b->items, b->cap * sizeof(LinkedList*));
    }
    LinkedList *copy = createList();                               // create a copy list
    copy_list_into(copy, src, word);                               // deep-copy nodes into copy
    *(b->items + b->count) = copy;                                 // store copy pointer
    b->count += 1;                                                 // increment count
}

void paths_free(PathBag *b) {
    for (int i = 0; i < b->count; ++i) {                           // free each stored LinkedList
        freeList(*(b->items + i));
    }
    free(b->items);                                                // free the container array
}

// !--------------------------------------------------------------
// Main function, DO NOT MODIFY
int main(int argc, char **argv) {
    if (argc != 2) {                                               // expect exactly one argument: puzzle filename
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");                                    // open puzzle file
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");                      // file open failure
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);                                  // read bSize (grid dimension)

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));          // allocate row pointers
    char *word = (char*)malloc(20 * sizeof(char));                 // allocate buffer for input word (max 19 chars + '\0')

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));        // allocate each row of bSize chars
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);                 // read char followed by space
        }
        fscanf(fptr, "%c \n", *(block + i) + j);                   // read last char in the row, then newline/space
    }
    fclose(fptr);                                                  // close puzzle file

    printf("Enter the word to search: ");
    scanf("%s", word);                                             // read search word from stdin

    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);                                            // display the grid

    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);                                     // perform the search

    return 0;                                                      // exit program
}

// !--------------------------------------------------------------

// Completed
void printPuzzle(char** arr) {
    for (int i = 0; i < bSize; i++) {                              // iterate rows
        for (int j = 0; j < bSize; j++) {                          // iterate columns
            printf("%c ", *(*(arr + i) + j));                      // print char with space
        }
        printf("\n");                                              // newline per row
    }
}

// allows case insensitive comparison of letters due to ASCII values
int compareLetters(char a, char b) {
    if (a == b || a + 32 == b || a - 32 == b) {                    // match exact or ASCII case offset
        return 1;
    }
    return 0;                                                      // not equal (case-insensitive)
}

// Helper function to create an empty 2D integer array
int **create_empty_array(int size) {
    int **result = (int**)malloc(size * sizeof(int*));             // allocate row pointers
    for (int i = 0; i < size; i++) {
        *(result + i) = (int*)malloc(size * sizeof(int));          // allocate each row
    }
    for (int i = 0; i < size; i++) {                               // zero-initialize all cells
        for (int j = 0; j < size; j++) {
            *(*(result + i) + j) = 0;
        }
    }
    return result;                                                 // return matrix
}

void mark_possible_start(char **arr, int size, char first_letter, int **Path_Array) {
    for (int i = 0; i < size; i++) {                               // scan grid for starting letters
        for (int j = 0; j < size; j++) {
            if (compareLetters(*(*(arr + i) + j), first_letter)) { // if matches first letter (case-insensitive)
                *(*(Path_Array + i) + j) = -999;                   // mark as start candidate with sentinel -999
            }
        }
    }
}

void print_int_array(int** arr, int size) {
    for (int i = 0; i < size; i++) {                               // print matrix row by row
        for (int j = 0; j < size; j++) {
            printf("%5d ", *(*(arr + i) + j));                     // fixed-width numbers
        }
        printf("\n");
    }
}


// Search in all 8 directions from the given position
int search_from_position(char** arr, char* word, int row, int col) {
    int pass = 0;
    for (pass = 0; pass < 2; pass++) {           // pass 0: prefer revisits, pass 1: any valid // two-phase selection
        for (int k = 0; k < 3; k++) {                                 // neighborhood rows (-1..+1)
            for (int l = 0; l < 3; l++) {                             // neighborhood cols (-1..+1)
                if (k == 1 && l == 1) continue;  // skip the current cell (center 3x3 neighborhood)

                int newRow = row + (k - 1);                           // candidate neighbor row
                int newCol = col + (l - 1);                           // candidate neighbor col
                if (newRow < 0 || newRow >= bSize || newCol < 0 || newCol >= bSize)
                    continue;                                         // bounds check

                // next expected character in word (by current path length)
                char nextCh = *(word + get_list_length(list));        // char we need next

                // usual guards
                if (!compareLetters(*(*(arr + newRow) + newCol), nextCh)) continue; // neighbor must match next char
                if ((get_last_node(list)->increment + 1) == -*(*(Possible_Paths + newRow) + newCol)) continue; // avoid immediate backtrack to cell flagged with negative of next index
                if (*(*(attemps_grid + newRow) + newCol) >= 3) continue; // don't over-try same neighbor

                // check if this cell has been used in the current path
                Node *seen = check_child_at_location(list, newRow, newCol); // detect reuse of cell in current path

                // pass 0 chooses a previously-used cell first (to produce "42" etc.)
                // pass 1 accepts any valid cell
                if ((pass == 0 && seen != NULL) || (pass == 1)) {     // phase-based selection rule
                    append(list, 1, newRow, newCol, word);            // extend path with neighbor
                    return 1;                                         // success: extended by one
                }
            }
        }
    }
    return 0; // none found                                            // no valid neighbor to extend
}

void mark_path(int** Path_Array, LinkedList* list) {
    Node* temp = list->head;                                          // iterate through nodes in current path
    while (temp != NULL) {
        *(*(Path_Array + temp->row) + temp->col) = temp->increment;   // write visit order index into matrix
        if(DEBUG == 1) {
            printf("Marking path at (%d,%d) with %d\n", temp->row, temp->col, temp->increment); // optional debug
        }
        temp = temp->next;
    }
}

// number concat helpers
int return_hights_place(int number) {
    int result = 0;                                                   // counts digits in number
    while (number > 0) {
        number /= 10;
        result++;
    }
    return result;                                                    // returns digit count
}
int return_number_readyToPaste(int number_to_add, int number) {
    int highest_place = return_hights_place(number_to_add); // make space for the new number // digits of left part
    int result = 0;
    for (int i = 0; i < highest_place; i++) {
        number *= 10;                                                 // shift right part by digits
    }
    result += number_to_add;                                          // place left part
    result += number;                                                 // append right part
    return result;                                                    // concatenated number
}

// Pretty Path Printing (single path)
void pretty_print_path(int** Path_Array, LinkedList* pathList) {
    Path_Array = create_empty_array(bSize); // Reset for final path  // allocate fresh matrix to display one path

    // Properly format the path numbers
    Node* temp = pathList->head;                                     // iterate nodes in provided path
    while (temp != NULL) {
        // fixed precedence: dereference full cell value first
        if (*(*(Path_Array + temp->row) + temp->col) > 0) {          // if already has digits, concatenate
            *(*(Path_Array + temp->row) + temp->col) =
                return_number_readyToPaste(*(*(Path_Array + temp->row) + temp->col), temp->increment);
        } else {
            *(*(Path_Array + temp->row) + temp->col) = temp->increment; // else store first visit index
        }
        if(DEBUG == 1) {
            printf("Marking path at (%d,%d) with %d\n", temp->row, temp->col, temp->increment); // debug
        }
        temp = temp->next;
    }

    print_int_array(Path_Array, bSize);                              // print the formatted path matrix

    // free the created matrix
    for (int r = 0; r < bSize; ++r) free(*(Path_Array + r));         // free rows
    free(Path_Array);                                                // free row pointer array
}

//Bonus: in the same matrix fix
// Combine one found path into an existing matrix (overlay: 2,4,6 -> 246)
void accumulate_path_into(int** Mat, LinkedList* pathList) {
    Node* t = pathList->head;                                        // iterate path nodes
    while (t != NULL) {
        int *cell = (*(Mat + t->row) + t->col);                      // pointer to target matrix cell
        if (*cell > 0) {
            *cell = return_number_readyToPaste(*cell, t->increment); // concatenate visit index
        } else {
            *cell = t->increment;                                    // first index at this cell
        }
        t = t->next;
    }
}


// bonus: print all distinct-start paths
void searchPuzzle(char** arr, char* word) {
    Possible_Paths = create_empty_array(bSize);                      // allocate path-marking matrix
    attemps_grid   = create_empty_array(bSize);                      // allocate attempts-count matrix
    mark_possible_start(arr, bSize, *word, Possible_Paths);          // mark all cells matching first char

    PathBag results;                                                 // container for all found full paths
    paths_init(&results, bSize * bSize > 0 ? bSize * bSize : 1);     // initial capacity

    for (int i = 0; i < bSize; ++i) {                                // iterate all rows
        for (int j = 0; j < bSize; ++j) {                            // iterate all cols
            if (*(*(Possible_Paths + i) + j) != -999) continue;      // only start from marked start cells

            for (int r = 0; r < bSize; ++r)                          // reset attempts grid to zeros
                for (int c = 0; c < bSize; ++c)
                    *(*(attemps_grid + r) + c) = 0;

            list = createList();                                     // create a fresh path list
            append(list, 1, i, j, word);                             // push starting cell
            global_breakout = 1;                                     // enable searching

            while (global_breakout == 1 && get_list_length(list) < (int)strlen(word)) { // search until fail or complete
                int sr = get_last_node(list)->row;                   // current end row
                int sc = get_last_node(list)->col;                   // current end col

                global_breakout = search_from_position(arr, word, sr, sc); // try to extend path

                if (global_breakout == 0) {                          // if stuck, backtrack
                    (*(*(attemps_grid + sr) + sc))++;                // increment attempts for that tail cell
                    *(*(Possible_Paths + sr) + sc) = -get_last_node(list)->increment; // mark as backtracked with -index
                    remove_last(list);                               // pop last node
                    global_breakout = (list->head != NULL) ? 1 : 0;  // continue only if path not empty
                }

                if (list->head == NULL) break;                       // no path left from this start

                if (get_list_length(list) == (int)strlen(word)) {    // found full word
                    paths_add(&results, list, word);                 // save a copy of the path
                    break;                                           // stop exploring from this start (one path)
                }
            }

            freeList(list);                                          // free working path list
            list = NULL;                                             // clear global pointer
        }
    }

    if (results.count > 0) {
        printf("Word found!\n");
        printf("Printing the search path:\n");

        // build one combined matrix from all paths
        int **combined = create_empty_array(bSize);                  // matrix to overlay all found paths
        for (int k = 0; k < results.count; ++k) {
            accumulate_path_into(combined, *(results.items + k));    // concat indices per cell across paths
        }
        print_int_array(combined, bSize);                            // show combined path matrix

        for (int r = 0; r < bSize; ++r) free(*(combined + r));       // free combined rows
        free(combined);                                              // free combined pointer array
        paths_free(&results);                                        // free all stored path lists
    } else {
        printf("Word not found!\n");                                 // no paths matched the word
        paths_free(&results);                                        // still free container
    }

    // free global matrices
    for (int r = 0; r < bSize; ++r) free(*(Possible_Paths + r));     // free Possible_Paths rows
    free(Possible_Paths);                                            // free row pointers
    for (int r = 0; r < bSize; ++r) free(*(attemps_grid + r));       // free attemps_grid rows
    free(attemps_grid);                                              // free row pointers
}

/* This program reads a square letter grid from a file and asks the user for a word.
It then searches the grid in all directions (up, down, diagonals) to find paths that spell the word.
Each path is stored using a custom linked list that keeps track of row, column, and letter positions.
If the word is found, it prints a grid showing the order of letters that form the word.
If not, it simply says the word wasn’t found.
Overall, it’s a word-search solver that tracks and prints the path of found words.
*/

//searches horizontally, vertically, and diagonally in every direction from each starting letter.