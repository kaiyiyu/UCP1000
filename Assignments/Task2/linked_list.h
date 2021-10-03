/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This is the header file for the functions and structs of the
    generic linked list.
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ListNode 
{
    void* value;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct LinkedList 
{
    int count;
    ListNode* head;
    ListNode* tail;
} LinkedList;

LinkedList* createLinkedList();
void insertFirst(LinkedList* list, void* in_value);
void* removeFirst(LinkedList* list);
void insertLast(LinkedList* list, void* in_value);
void* removeLast(LinkedList* list);
void printLinkedList(LinkedList* list);
void freeLinkedList(LinkedList* list);

#endif