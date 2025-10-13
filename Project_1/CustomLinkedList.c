#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int valid_path;
    int row, col, increment;
    char letter;
    struct Node* next;
    struct Node* prev;
} Node;

// Linked list structure
typedef struct LinkedList {
    Node* head;
} LinkedList;

// Create a new linked list
LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

// Add a node to the end
void append(LinkedList* list, int valid_path, int row, int col, char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->valid_path = valid_path;
    newNode->row = row;
    newNode->col = col;
    
    newNode->next = NULL;

    if (list->head == NULL) {
        newNode->increment = 1; // First node
        list->head = newNode;

    } else {
        Node* temp = list->head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
        newNode->increment = temp->increment + 1;
    }
    newNode->letter = *(word + newNode->increment);
}

// Print the list
void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%c -> ", temp->letter);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free the list
void freeList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}
Node *check_child_at_location(LinkedList* list, int row, int col)
{
    Node* temp = list->head;
    while (temp != NULL) {
        if(temp->row == row && temp->col == col)
            return temp; // Found at location
        temp = temp->next;
    }
    return NULL; // Not found at location
}
int is_child_valid(Node* child)
{
    if(child->valid_path == 1)
        return 1; // Not found
    return 0; // Return valid_path status
}

char* get_path_as_string(LinkedList* list) {
    Node* temp = list->head;
    int length = 0;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    char* path = (char*)malloc((length + 1) * sizeof(char));
    temp = list->head;
    for (int i = 0; i < length; i++) {
        path[i] = temp->letter;
        temp = temp->next;
    }
    path[length] = '\0'; // Null-terminate the string
    return path;
}
int get_list_length(LinkedList* list) {
    Node* temp = list->head;
    int length = 0;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}
void remove_last(LinkedList* list) {
    if (list->head == NULL) return; // List is empty

    if (list->head->next == NULL) {
        free(list->head);
        list->head = NULL; // List had one node
    } else {
        Node* temp = list->head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->prev->next = NULL; // Remove last node
        free(temp);
    }
}
Node* get_last_node(LinkedList* list) {
    if (list->head == NULL) {
        // List is empty
        return NULL;
    }

    Node* temp = list->head;
    while (temp->next != NULL)
        temp = temp->next;
    return temp; // Return the last node
}


// // Example usage
// int main() {
//     LinkedList* list = createList();
//     append(list, 1, 0, 0, 'A');
//     append(list, 1, 0, 1, 'B');
//     append(list, 1, 0, 2, 'C');

//     printList(list);

//     if(check_child_at_location(list, 0, 1) != NULL) {
//         printf("Node found at (0,1), Valid?\n");
//         printf("%d\n", is_child_valid(check_child_at_location(list, 0, 1)));
//         printf("Path: %s\n", get_path_as_string(list));
//     } else {
//         printf("Node not found at (0,1)\n");
//     }
//     freeList(list);
//     return 0;
// }
