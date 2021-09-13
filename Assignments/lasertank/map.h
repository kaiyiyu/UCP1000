/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This is the header file for the functions of the game map.
*/

#ifndef MAP_H
#define MAP_H

#include "structs.h"
#include "linked_list.h"

char** createMap(Map* map);
int initializeMirrors(Map* map, Mirrors* mirror[], int count);
void printMap(Map* map, LinkedList* logs);
int checkWin(Map* map, Tanks* player, Tanks* enemy, LinkedList* logs);
void freeMap(Map* map);

#endif