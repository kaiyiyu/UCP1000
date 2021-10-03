/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This file contains all functions for the allocation, heap freeing, 
    and condition checking of the game map.
*/

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/* Functions are mostly similar to task 1 submission except for the use of structs */

char** createMap(Map* map)
{   
    char **array = malloc(map->row*sizeof(char*));
        int i, j;
        for (i = 0; i < map->row; i++) 
        {
            array[i] = malloc((map->column + 1) * sizeof(char)); /* + 1 for null terminator */
        }

    /* Assign '*' to map borders. */
    for (i = 0; i < map->row; i++)
        {
            for (j = 0; j < map->column; j++) 
            {
                 if (i == 0 || i == map->row - 1 || j == 0 || j == map->column - 1) 
                {
                    array[i][j] = '*';
                }
                else 
                {
                    array[i][j] = ' ';
                }
            }
        }
    return array;
}

/* Initialize mirrors if present */
int initializeMirrors(Map* map, Mirrors* mirror[], int count)
{   
    if (count != 0)
    {
        int i;
        for (i = 0; i < count; i++)
        {
            if (mirror[i]->slash == 'f')
            {
            map->array[mirror[i]->row][mirror[i]->column] = '/';
            }
            else if (mirror[i]->slash == 'b')
            {
            map->array[mirror[i]->row][mirror[i]->column] = '\\';
            }
        } 
    }
    return 0;
}

void printMap(Map* map, LinkedList* logs)
{
    system("clear");
    printf("======================================\nGLITCHY C IMPLEMENTATION OF LASER TANK\n======================================\n");
    
    /* ANSI color codes for regular bold text from 
    https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a#file-ansi-color-codes-h */
    char* colors[6];
    colors[0] = "\e[1;31m";
    colors[1] = "\e[1;32m";
    colors[2] = "\e[1;33m";
    colors[3] = "\e[1;34m";
    colors[4] = "\e[1;35m";
    colors[5] = "\e[1;36m";
    
    int i, j;
    for (i = 0; i < map->row; i++)
    {
        for (j = 0; j < map->column; j++) 
        {
            if (map->array[i][j] == '|' || map->array[i][j] == '-')
            {
                /* Exit color code every character to change color each reprint of laser. */
                static int itr;
                printf("%s%c\e[0m ", colors[itr], map->array[i][j]);
                itr++;

                /* Reset back count itr to 0. */
                if (itr == 6) 
                {
                    itr = 0;
                }
            }
            else if (map->array[i][j] == 'X') /* Red text to indicate destroyed tank. */
            {
                printf("%s%c\e[0m ", colors[0], map->array[i][j]);
            }
            else if (map->array[i][j] == '\\' || map->array[i][j] == '/') 
            {
                printf("\e[1;31m%c\e[0m ", map->array[i][j]);
            }
            else
            {
                printf("%c ", map->array[i][j]);
            }
        }
        printf("\n");
    }
    void* ptr = map->array;
    insertLast(logs, ptr);
}

int checkWin(Map* map, Tanks* player, Tanks* enemy, LinkedList* logs)
{
    int condition = 0;
    if (map->array[player->row][player->column] == 'X')
    {
        /* Print current map state and red background message if lose. */
        printMap(map, logs);
        printf("\e[41mYOU LOSE! Better luck next time.\e[0m\n"); 
        condition = 1;
    }
    else if (map->array[enemy->row][enemy->column] == 'X')
    {
        /* Print current map state and green background message if win. */
        printMap(map, logs);
        printf("\e[42mYOU WIN! Congratulations.\e[0m\n"); /* green background */
        condition = 1;
    }
    return condition;
}

void freeMap(Map* map)
{
    int i;
    for (i = 0; i < map->row; i++)
        {
            free(map->array[i]);
            map->array[i] = NULL;
        }
        free(map->array);
        map->array = NULL;
}