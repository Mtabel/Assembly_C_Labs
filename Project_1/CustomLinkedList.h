#ifndef CUSTOM_LINKED_LIST_H
#define CUSTOM_LINKED_LIST_H

typedef struct Node {
    int valid_path;
    int row, col, increment;
    char letter;
    struct Node* next;
    struct Node* prev;
} Node;
typedef struct LinkedList {
    Node* head;
} LinkedList;
    
    LinkedList* createList();
    void append(LinkedList* list, int valid_path, int row, int col, char* word);
    void printList(LinkedList* list);
    void freeList(LinkedList* list);
    Node *check_child_at_location(LinkedList* list, int row, int col);
    int is_child_valid(Node* node);
    char* get_path_as_string(LinkedList* list);
    int get_list_length(LinkedList* list);
    void remove_last(LinkedList* list);
    void get_last_node(LinkedList* list, Node** node);
    
#endif /* CUSTOM_LINKED_LIST_H */