/*
    Author: Kai-Yu Yu (90022616)
    Date: August 14, 2021
    Purpose: This file contains the function for player and
    enemy tank to shoot their opponent.
*/

#include <stdio.h>
#include <stdlib.h>
#include "laser.h"
#include "map.h"
#include "ucpSleep.h"

/**
 * @brief This function takes in the pointers for the coordinates of a tank which contains the current
 *        value of its position in the map then stores it in an int for the start of the laser animation without 
 *        changing the position of the tank itself. 
 * 
 * @param map - Allocated 2D character array 
 * @param rows - Map row size
 * @param cols - Map column size
 * @param tank_row - Current row index of player/enemy tank
 * @param tank_col - Current column index of player/enemy tank
 * @param opponent_row - Current row index of opposing tank
 * @param opponent_col - Current column index of opposing tank
 */
void shootLaser(char** map, int rows, int cols, int* tank_row, int* tank_col, int* opponent_row, int* opponent_col)
{
    int t_row = *tank_row;
    int t_col = *tank_col;

    if (map[t_row][t_col] == '^')
    {   /* Upward (row-1) animation which changes the value and row index accordingly then
           resets previous row index to empty " ". */
        while (map[t_row - 1][t_col] == ' ')
        {
            t_row -= 1;
            map[t_row][t_col] = '|';
            printMap(map, rows, cols);
            map[t_row][t_col] = ' ';
            ucpSleep(0.10);
        }
        if (map[t_row - 1][t_col] == map[*opponent_row][*opponent_col])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map[*opponent_row][*opponent_col] = 'X';
        }
    }
    else if (map[t_row][t_col] == 'v')
    {   /* Downward (row+1) animation which changes the value and row index accordingly then
           resets previous row index to empty " ". */
        while (map[t_row + 1][t_col] == ' ')
        {
            t_row += 1;
            map[t_row][t_col] = '|';
            printMap(map, rows, cols);
            map[t_row][t_col] = ' ';
            ucpSleep(0.10);
        }
        if (map[t_row + 1][t_col] == map[*opponent_row][*opponent_col])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map[*opponent_row][*opponent_col] = 'X';
        }
    }
    else if (map[t_row][t_col] == '>')
    {   /* Rightward (col+1) animation which changes the value and column index accordingly then
           resets previous column index to empty " ". */
        while (map[t_row][t_col + 1] == ' ')
        {
            t_col += 1;
            map[t_row][t_col] = '-';
            printMap(map, rows, cols);
            map[t_row][t_col] = ' ';
            ucpSleep(0.10);
        }
        if (map[t_row][t_col + 1] == map[*opponent_row][*opponent_col])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map[*opponent_row][*opponent_col] = 'X';
        }
    }
    else if (map[t_row][t_col] == '<')
    {   /* Leftward (col-1) animation which changes the value and column index accordingly then
           resets previous column index to empty " ". */
        while (map[t_row][t_col - 1] == ' ')
        {
            t_col -= 1;
            map[t_row][t_col] = '-';
            printMap(map, rows, cols);
            map[t_row][t_col] = ' ';
            ucpSleep(0.10);
        }
        if (map[t_row][t_col - 1] == map[*opponent_row][*opponent_col])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map[*opponent_row][*opponent_col] = 'X';
        }
    }
}
