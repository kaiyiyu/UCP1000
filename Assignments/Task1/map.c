/*
    Author: Kai-Yu Yu (90022616)
    Date: August 14, 2021
    Purpose: This file contains all functions for the allocation, heap freeing, and
    condition checking of the game map.
*/

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/**
 * @brief This function takes in the command line arguments for row size and column size
 *        to create and allocate memory for the game map.
 * 
 * @param rows - Map row size
 * @param columns - Map column size
 * @return char** game map array 
 */
char** createMap(int rows, int columns)
{   
    char **map = malloc(rows*sizeof(char*));
        int i, j;
        for (i = 0; i < rows; i++) 
        {
            map[i] = malloc((columns + i) * sizeof(char)); /* + 1 for null terminator */
        }

    /* Assign '*' to map borders. */
    for (i = 0; i < rows; i++)
        {
            for (j = 0; j < columns; j++) 
            {
                 if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) 
                {
                    map[i][j] = '*';
                }
                else 
                {
                    map[i][j] = ' ';
                }
            }
        }
    return map;
}

/**
 * @brief This function clears terminal screen after each round and prints
 *        the current state of the game map.
 * 
 * @param map - Allocated 2D character array
 * @param rows - Map row size
 * @param columns - Map column size
 */
void printMap(char** map, int rows, int columns)
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
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++) 
        {
            if (map[i][j] == '|' || map[i][j] == '-')
            {
                 /* Exit color code every character to change color each reprint of laser. */
                static int itr;
                printf("%s%c\e[0m ", colors[itr], map[i][j]);
                itr++;

                /* Reset back count itr to 0. */
                if (itr == 6) 
                {
                    itr = 0;
                }
            }
            else if (map[i][j] == 'X') /* Red text to indicate destroyed tank. */
            {
                printf("%s%c\e[0m ", colors[0], map[i][j]);
            }
            else
            {
                printf("%c ", map[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * @brief This function looks for any destroyed tank in the game map and returns int 1 if found
 *        then declares the winning condition.
 * 
 * @param map - Allocated 2D character array 
 * @param rows - Map row size
 * @param cols - Map column size
 * @param p_row - Pointer to current row index of player tank
 * @param p_col - Pointer to current column index of player tank
 * @param e_row - Pointer to current row index of enemy tank
 * @param e_col - Pointer to current column index of enemy tank
 * @return int 0 when no destroyed tank and 1 when there is a destroyed tank
 */
int checkWin(char** map, int rows, int cols, int* p_row, int* p_col, int* e_row, int* e_col)
{
    int condition = 0;
    if (map[*p_row][*p_col] == 'X')
    {
        /* Print current map state and red background message if lose. */
        printMap(map, rows, cols);
        printf("\e[41mYOU LOSE! Better luck next time.\e[0m\n"); 
        condition = 1;
    }
    else if (map[*e_row][*e_col] == 'X')
    {
        /* Print current map state and green background message if win. */
        printMap(map, rows, cols);
        printf("\e[42mYOU WIN! Congratulations.\e[0m\n"); /* green background */
        condition = 1;
    }
    return condition;
}

/**
 * @brief This function frees the memory allocated for the 2D array of the program.
 * 
 * @param map - Allocated 2D character array
 * @param rows - Map row size
 */
void freeMap(char** map, int rows)
{
    int i;
    for (i = 0; i < rows; i++)
        {
            free(map[i]);
            map[i] = NULL;
        }
        free(map);
        map = NULL;
}