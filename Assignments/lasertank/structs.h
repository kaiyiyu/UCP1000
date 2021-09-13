/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 12, 2021
    Purpose: This is the header file for the structs and allocating
    functions.
*/

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    int row;
    int column;
    char** array;
} Map;

typedef struct
{
    int row;
    int column;
    char slash;
} Mirrors;

typedef struct
{
    int row;
    int column;
    char direction;
} Tanks;

Map* createMapStruct(int row, int column);
Tanks* createPlayerStruct(int row, int column, char direction);
Tanks* createEnemyStruct(int row, int column, char direction);
void createMirrorStruct(Mirrors* mirror, int row, int col, char slash);
void freeStructs(Map* map, Tanks* player, Tanks* enemy, Mirrors* mirror[], int count);

#endif