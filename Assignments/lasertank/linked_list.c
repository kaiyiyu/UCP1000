/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This file contains the implementation of a generic linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void insertFirst(LinkedList* list, void* in_value)
{
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = in_value;
    
    if (list->head == NULL)
    { 
        list->head = new_node;
        list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else
    { 
        list->head->prev = new_node;
        new_node->next = list->head;
        new_node->prev = NULL;
        list->head = new_node;
    }
    list->count += 1;
}

void* removeFirst(LinkedList* list)
{
    void* out_value = NULL;
    ListNode* del_node = NULL;
    
    if (list->head != NULL)
    {
        del_node = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        out_value = del_node->value;
        free(del_node);
    }
    list->count -= 1;
    return out_value;
}

void insertLast(LinkedList* list, void* in_value)
{
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->value = in_value;
    new_node->next = NULL;

    if (list->tail == NULL)
    { 
        list->head = new_node;
        list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    else
    { 
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
        new_node->next = NULL;
    }
    list->count += 1;
}

void* removeLast(LinkedList* list)
{
    void* out_value = NULL;
    ListNode* del_node = NULL;

    if (list->tail != NULL)
    {
        del_node = list->tail;
        if (list->tail->prev == NULL)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
        out_value = del_node->value;
        free(del_node); /*edit if will use the data somewhere else*/
    }
    list->count -= 1;
    return out_value;
}

void printLinkedList(LinkedList* list)
{
    ListNode* curr_node;
    curr_node = list->head;

    while (curr_node != NULL)
    {
        printf("%s,",(char*)curr_node->value);
        curr_node = curr_node->next;
    }
    printf("\n");
}

void freeLinkedList(LinkedList* list)
{
    ListNode* curr_node; 
    ListNode* next_node;
    curr_node = list->head;
    while (curr_node != NULL)
    {
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }
    free(list);
    list = NULL;
}