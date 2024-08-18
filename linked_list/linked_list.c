#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// initialize the linked list
void initializeList(LinkedList *list)
{
    list->head = NULL;
}

// insert a new node with the given value
bool Insert(LinkedList *list, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return false;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (list->head == NULL || list->head->data > value)
    {
        newNode->next = list->head;
        list->head = newNode;
    }
    else
    {
        Node *current = list->head;
        while (current->next != NULL && current->next->data < value)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return true;
}

// search for a node with the given value
bool Member(LinkedList *list, int value)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (current->data == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// delete a node with the given value
bool Delete(LinkedList *list, int value)
{
    if (list->head == NULL)
    {
        return false;
    }
    if (list->head->data == value)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        return true;
    }
    Node *current = list->head;
    while (current->next != NULL && current->next->data != value)
    {
        current = current->next;
    }
    if (current->next != NULL)
    {
        Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        return true;
    }
    return false;
}

// Print the linked list
void printList(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
