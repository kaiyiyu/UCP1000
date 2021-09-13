/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 12, 2021
    Purpose: This file contains all functions for creating and allocating
    the structs used in the program.
*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

/* Separate file for typedefs (.h) and functions (.c) to allocate each struct */

Map* createMapStruct(int row, int column)
{
    Map* map = (Map*)malloc(sizeof(Map));
    map->row = row;
    map->column = column;
    map->array = NULL;

    return map;
}

Tanks* createPlayerStruct(int row, int column, char direction)
{
    Tanks* player = (Tanks*)malloc(sizeof(Tanks));
    player->row = row;
    player->column = column;
    player->direction = direction;

    return player;
}

Tanks* createEnemyStruct(int row, int column, char direction)
{
    Tanks* enemy = (Tanks*)malloc(sizeof(Tanks));
    enemy->row = row;
    enemy->column = column;
    enemy->direction = direction;

    return enemy;
}

void createMirrorStruct(Mirrors* mirror, int row, int col, char slash)
{
    mirror->row = row;
    mirror->column = col;
    mirror->slash = slash;
}

void freeStructs(Map* map, Tanks* player, Tanks* enemy, Mirrors* mirror[], int count)
{
    free(map);
    map = NULL;

    free(player);
    player = NULL;

    free(enemy);
    enemy = NULL;

    int i;
    if (count != 0)
    {
        for (i = 0; i < count; i++)
        {
            free(mirror[i]);
            mirror[i] = NULL;
        }
    }
}