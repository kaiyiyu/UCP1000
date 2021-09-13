/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This is the header file for the file IO functions.
*/

#ifndef FILE_H
#define FILE_H

#include "linked_list.h"
#include "structs.h"

int countLines(char* filename);
int readFile(char* filename, int* mrow, int* mcol, int* prow, int* pcol, char* pdir, int* erow, int* ecol, char* edir, int row[], int col[], char dir[]);
int writeFile(char* filename, LinkedList* logs, Map* map);

#endif