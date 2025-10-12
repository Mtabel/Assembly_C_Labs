#include <stdio.h>
#include "CustomLinkedList.h"
int main() {

    LinkedList* list = createList();
    append(list, 1, 0, 0, 'A');
    append(list, 1, 0, 1, 'B');
    append(list, 1, 0, 2, 'C');

    printList(list);

    if(check_child_at_location(list, 0, 1) != NULL) {
        printf("Node found at (0,1), Valid?\n");
        printf("%d\n", is_child_valid(check_child_at_location(list, 0, 1)));
        printf("Path: %s\n", get_path_as_string(list));
    } else {
        printf("Node not found at (0,1)\n");
    }
    freeList(list);
    return 0;
}