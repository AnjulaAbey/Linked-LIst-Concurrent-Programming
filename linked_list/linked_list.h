#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

// Node structure definition

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Linked list structure definition

typedef struct LinkedList {
    Node *head;
} LinkedList;

// Function declaration

void initializeList(LinkedList *list);
bool Insert(LinkedList *list, int value);
bool Member(LinkedList *list, int value);
bool Delete(LinkedList *list, int value);
void PrintList(LinkedList *list);

#endif