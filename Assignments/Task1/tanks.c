/*
    Author: Kai-Yu Yu (90022616)
    Date: August 14, 2021
    Purpose: This file contains all functions for the player and enemy tanks
    including player movement, collision check, and enemy target area.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tanks.h"
#include "laser.h"
#include "ucpSleep.h"

/**
 * @brief This function takes in the command line arguments to initialize player
 *        tank in the allocated array. 
 * 
 * @param map - Allocated 2D character array 
 * @param p_row - Pointer to current row index of player tank
 * @param p_col - Pointer to current column index of player tank
 * @param p_dir - Pointer to value of player direction
 */
void initializePlayer(char** map, int* p_row, int* p_col, char* p_dir)
{   
    if (strcmp(p_dir, "n") == 0)
    {
        map[*p_row][*p_col] = '^';
    }
    else if (strcmp(p_dir, "s") == 0)
    {
        map[*p_row][*p_col] = 'v';
    }
    else if (strcmp(p_dir, "e") == 0)
    {
        map[*p_row][*p_col] = '>';
    }
    else if (strcmp(p_dir, "w") == 0)
    {
        map[*p_row][*p_col] = '<';
    }
}

/**
 * @brief This function takes in the command line arguments to initialize enemy
 *        tank in the allocated array. 
 * 
 * @param map - Allocated 2D character array 
 * @param e_row - Pointer to current row index of enemy tank
 * @param e_col - Pointer to current column index of enemy tank
 * @param e_dir - Pointer to value of enemy direction
 */
void initializeEnemy(char** map, int* e_row, int* e_col, char* e_dir)
{   
    if (strcmp(e_dir, "n") == 0)
    {
        map[*e_row][*e_col] = '^';
    }
    else if (strcmp(e_dir, "s") == 0)
    {
        map[*e_row][*e_col] = 'v';
    }
    else if (strcmp(e_dir, "e") == 0)
    {
        map[*e_row][*e_col] = '>';
    }
    else if (strcmp(e_dir, "w") == 0)
    {
        map[*e_row][*e_col] = '<';
    }
}

/**
 * @brief This function prints user instruction and asks for command input.
 * 
 * @return char direction/movement of player tank
 */
char askCommand()
{
    char command;
    
    printf("[w] to go/face up\n[s] to go/face down\n[a] to go/face left\n[d] to go/face right\n[f] to shoot laser\n\e[43maction:\e[0m\n");
    scanf("%c", &command);

    return command;
}

/**
 * @brief This function moves player tank across the map and executes laser animation 
 *        according to user input.
 * 
 * @param map - Allocated 2D character array 
 * @param rows - Map row size
 * @param cols - Map column size
 * @param p_row - Pointer to current row index of player tank
 * @param p_col - Pointer to current column index of player tank
 * @param e_row - Pointer to current row index of enemy tank
 * @param e_col - Pointer to current column index of enemy tank
 */
void movePlayer(char** map, int rows, int cols, int* p_row, int* p_col, int* e_row, int* e_col)
{
    char command = askCommand();

    if (command == 'w')
    {
        if (map[*p_row - 1][*p_col] != ' ' && map[*p_row][*p_col] == '^')
        { /* Check for first row border collision. */
            warnCollision();
        }
        else if (map[*p_row][*p_col] == '^')
        {   /* Move row index if next is empty otherwise keep current condition. */
            map[*p_row][*p_col] = ' ';
            *p_row -= 1;
        }
        map[*p_row][*p_col] = '^';
    }
    else if (command == 's')
    {
        if (map[*p_row + 1][*p_col] != ' ' && map[*p_row][*p_col] == 'v')
        {   /* Check for last row border collision. */
            warnCollision();
        }
        else if (map[*p_row][*p_col] == 'v')
        {   /* Move row index if next is empty otherwise keep current condition. */
            map[*p_row][*p_col] = ' ';
            *p_row += 1;
        }
        map[*p_row][*p_col] = 'v';
    }
    else if (command == 'a')
    {
        if (map[*p_row][*p_col - 1] != ' ' && map[*p_row][*p_col] == '<')
        {   /* Check for left column border collision. */
            warnCollision();
        }
        else if (map[*p_row][*p_col] == '<')
        {   /* Move column index if next is empty otherwise keep current condition. */
            map[*p_row][*p_col] = ' ';
            *p_col -= 1;
        }
        map[*p_row][*p_col] = '<';
    }
    else if (command == 'd')
    {
        if (map[*p_row][*p_col + 1] != ' ' && map[*p_row][*p_col] == '>')
        {   /* Check for right column border collision. */
            warnCollision();
        }
        else if (map[*p_row][*p_col] == '>')
        {   /* Move column index if next is empty otherwise keep current condition. */
            map[*p_row][*p_col] = ' ';
            *p_col += 1;
        }
        map[*p_row][*p_col] = '>';   
    }
    else if (command == 'f')
    {   /* Execute laser animation */
        shootLaser(map, rows, cols, p_row, p_col, e_row, e_col);
    }
}

/**
 * @brief This function prints a border or enemy tank collision warning.
 * 
 * @return int 0 if display of collision warning is successful.
 */
int warnCollision()
{
    printf("\e[1;31m!!! ERROR: Player can't move there. Input new player command. !!!\e[0m\n");
    ucpSleep(1.0);
    return 0;
}

/**
 * @brief This function scans the front of enemy tank after each player movement
 *        and executes laser animation if player tank is in target line.
 * 
 * @param map - Allocated 2D character array 
 * @param rows - Map row size
 * @param cols - Map column size
 * @param p_row - Pointer to current row index of player tank
 * @param p_col - Pointer to current column index of player tank
 * @param e_row - Pointer to current row index of enemy tank
 * @param e_col - Pointer to current column index of enemy tank
 */
void scanEnemyArea(char** map, int rows, int cols, int* p_row, int* p_col, int* e_row, int* e_col)
{
    if (*e_col == *p_col)
    {
        if (map[*e_row][*e_col] == '^' && *e_row > *p_row)
        { /* Check upper row indexes when player is in enemy column. */
            shootLaser(map, rows, cols, e_row, e_col, p_row, p_col);
        }
        else if (map[*e_row][*e_col] == 'v' && *e_row < *p_row)
        {   /* Check lower row indexes when player is in enemy column. */
            shootLaser(map, rows, cols, e_row, e_col, p_row, p_col);
        }
    }
    else if (*e_row == *p_row) 
    {
        if (map[*e_row][*e_col] == '<' && *e_col > *p_col)
        {   /* Check left column indexes when player is in enemy row. */
            shootLaser(map, rows, cols, e_row, e_col, p_row, p_col);
        }
        else if (map[*e_row][*e_col] == '>' && *e_col < *p_col)
        {   /* Check right column indexes when player is in enemy row. */
            shootLaser(map, rows, cols, e_row, e_col, p_row, p_col);
        }
    }
}
