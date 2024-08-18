#include <stdio.h>
#include "linked_list/linked_list.h"

int main() {
    LinkedList list;
    initializeList(&list);

    // Insert some values
    Insert(&list, 10);
    Insert(&list, 20);
    Insert(&list, 15);
    Insert(&list, 5);
    
    printList(&list);

    // Check membership
    printf("Is 15 in the list? %s\n", Member(&list, 15) ? "Yes" : "No");
    printf("Is 25 in the list? %s\n", Member(&list, 25) ? "Yes" : "No");

    // Delete a value
    Delete(&list, 10);
    printList(&list);

    return 0;
}
