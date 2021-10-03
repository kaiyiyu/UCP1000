/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 12, 2021
    Purpose: This file contains all functions for the character initialization
    and laser animations.
*/

#include <stdio.h>
#include <stdlib.h>
#include "ucpSleep.h"
#include "map.h"
#include "file_io.h"
#include "tanks.h"

/* Functions are mostly similar to task 1 submission except for the use of structs
   and combined laser.c with tank.c to one general file */

void initializePlayer(Map* map, Tanks* player)
{   
    if (player->direction == 'n')
    {
        map->array[player->row][player->column] = '^';
    }
    else if (player->direction == 's')
    {
        map->array[player->row][player->column] = 'v';
    }
    else if (player->direction == 'e')
    {
        map->array[player->row][player->column] = '>';
    }
    else if (player->direction == 'w')
    {
        map->array[player->row][player->column] = '<';
    }
}

void initializeEnemy(Map* map, Tanks* enemy)
{   
    if (enemy->direction == 'n')
    {
        map->array[enemy->row][enemy->column] = '^';
    }
    else if (enemy->direction == 's')
    {
        map->array[enemy->row][enemy->column] = 'v';
    }
    else if (enemy->direction == 'e')
    {
        map->array[enemy->row][enemy->column] = '>';
    }
    else if (enemy->direction == 'w')
    {
        map->array[enemy->row][enemy->column] = '<';
    }
}

/* Previous function as task 1 with use of structs and option to save log */
char askCommand()
{
    char command;
    
    printf("[w] to go/face up\n[s] to go/face down\n[a] to go/face left\n[d] to go/face right\n[f] to shoot laser\n[l] to save the Log\n\e[1;31maction:\e[0m\n");
    scanf("%c", &command);

    return command;
}

/* Previous function as task 1 with use of structs and option to save log */
void movePlayer(Map* map, Tanks* player, Tanks* enemy, LinkedList* logs, char* filename)
{
    char command = askCommand();

    if (command == 'w')
    {
        if (map->array[player->row - 1][player->column] != ' ' && map->array[player->row][player->column] == '^')
        { /* Check for first row border collision. */
            warnCollision();
        }
        else if (map->array[player->row][player->column] == '^')
        {   /* Move row index if next is empty otherwise keep current condition. */
            map->array[player->row][player->column] = ' ';
            player->row -= 1;
        }
        map->array[player->row][player->column] = '^';
    }
    else if (command == 's')
    {
        if (map->array[player->row + 1][player->column] != ' ' && map->array[player->row][player->column] == 'v')
        {   /* Check for last row border collision. */
            warnCollision();
        }
        else if (map->array[player->row][player->column] == 'v')
        {   /* Move row index if next is empty otherwise keep current condition. */
            map->array[player->row][player->column] = ' ';
            player->row += 1;
        }
        map->array[player->row][player->column] = 'v';
    }
    else if (command == 'a')
    {
        if (map->array[player->row][player->column - 1] != ' ' && map->array[player->row][player->column] == '<')
        {   /* Check for left column border collision. */
            warnCollision();
        }
        else if (map->array[player->row][player->column] == '<')
        {   /* Move column index if next is empty otherwise keep current condition. */
            map->array[player->row][player->column] = ' ';
            player->column -= 1;
        }
        map->array[player->row][player->column] = '<';
    }
    else if (command == 'd')
    {
        if (map->array[player->row][player->column + 1] != ' ' && map->array[player->row][player->column] == '>')
        {   /* Check for right column border collision. */
            warnCollision();
        }
        else if (map->array[player->row][player->column] == '>')
        {   /* Move column index if next is empty otherwise keep current condition. */
            map->array[player->row][player->column] = ' ';
            player->column += 1;
        }
        map->array[player->row][player->column] = '>';   
    }
    else if (command == 'f')
    {   /* Execute laser animation */
        shootLaser(map, player, enemy, logs);
    }
    else if (command == 'l')
    {   /* Print current state to file */
        printf("Saving log to file...\n");
        writeFile(filename, logs, map);
    }
}

int warnCollision()
{
    printf("\e[1;31m!!! ERROR: Player can't move there. Input new player command. !!!\e[0m\n");
    ucpSleep(1.0);
    return 0;
}

/* Previous function as task 1 with use of structs */
void scanEnemyArea(Map* map, Tanks* player, Tanks* enemy, LinkedList* logs)
{
    if (enemy->column == player->column)
    {
        if (map->array[enemy->row][enemy->column] == '^' && enemy->row > player->row)
        { /* Check upper row indexes when player is in enemy column. */
            shootLaser(map, enemy, player, logs);
        }
        else if (map->array[enemy->row][enemy->column] == 'v' && enemy->row < player->row)
        {   /* Check lower row indexes when player is in enemy column. */
            shootLaser(map, enemy, player, logs);
        }
    }
    else if (enemy->row == player->row) 
    {
        if (map->array[enemy->row][enemy->column] == '<' && enemy->column > player->column)
        {   /* Check left column indexes when player is in enemy row. */
            shootLaser(map, enemy, player, logs);
        }
        else if (map->array[enemy->row][enemy->column] == '>' && enemy->column < player->column)
        {   /* Check right column indexes when player is in enemy row. */
            shootLaser(map, enemy, player, logs);
        }
    }
}

/* Previous function as task 1 with use of structs */
void shootLaser(Map* map, Tanks* shooter, Tanks* opponent, LinkedList* logs)
{
    int s_row = shooter->row;
    int s_col = shooter->column;

    if (map->array[s_row][s_col] == '^')
    {   /* Upward (row-1) animation which changes the value and row index accordingly then
           resets previous row index to empty " ". */
        while (map->array[s_row - 1][s_col] == ' ')
        {
            s_row -= 1;
            map->array[s_row][s_col] = '|';
            printMap(map, logs);
            map->array[s_row][s_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[s_row - 1][s_col] == map->array[opponent->row][opponent->column])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map->array[opponent->row][opponent->column] = 'X';
        }
        else if (map->array[s_row - 1][s_col] == '\\' || map->array[s_row - 1][s_col] == '/')
        {   
            map->array[s_row][s_col] = '|';
        }
    }
    else if (map->array[s_row][s_col] == 'v')
    {   /* Downward (row+1) animation which changes the value and row index accordingly then
           resets previous row index to empty " ". */
        while (map->array[s_row + 1][s_col] == ' ')
        {
            s_row += 1;
            map->array[s_row][s_col] = '|';
            printMap(map, logs);
            map->array[s_row][s_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[s_row + 1][s_col] == map->array[opponent->row][opponent->column])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map->array[opponent->row][opponent->column] = 'X';
        }
        else if (map->array[s_row + 1][s_col] == '\\' || map->array[s_row + 1][s_col] == '/')
        {   
            map->array[s_row][s_col] = '|';
        }
    }
    else if (map->array[s_row][s_col] == '>')
    {   /* Rightward (col+1) animation which changes the value and column index accordingly then
           resets previous column index to empty " ". */
        while (map->array[s_row][s_col + 1] == ' ')
        {
            s_col += 1;
            map->array[s_row][s_col] = '-';
            printMap(map, logs);
            map->array[s_row][s_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[s_row][s_col + 1] == map->array[opponent->row][opponent->column])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map->array[opponent->row][opponent->column] = 'X';
        }
        else if (map->array[s_row][s_col + 1] == '\\' || map->array[s_row][s_col + 1] == '/')
        {   
            map->array[s_row][s_col] = '-';
        }
    }
    else if (map->array[s_row][s_col] == '<')
    {   /* Leftward (col-1) animation which changes the value and column index accordingly then
           resets previous column index to empty " ". */
        while (map->array[s_row][s_col - 1] == ' ')
        {
            s_col -= 1;
            map->array[s_row][s_col] = '-';
            printMap(map, logs);
            map->array[s_row][s_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[s_row][s_col - 1] == map->array[opponent->row][opponent->column])
        {   /* Check next coordinate for opposing tank and mark as 'X' when hit. */
            map->array[opponent->row][opponent->column] = 'X';
        }
        else if (map->array[s_row][s_col - 1] == '\\' || map->array[s_row][s_col - 1] == '/')
        {   
            map->array[s_row][s_col] = '-';
        }
    }
}

/* Same laser movement with shootLaser function. For any mirror in the array, if a laser '-'
or '|' is a cell away, it will change the direction of the laser depending on the mirror orientation */
void deflectLaser(Map* map, Mirrors* mirror, Tanks* player, Tanks* enemy, LinkedList* logs)
{
    int m_row = mirror->row;
    int m_col = mirror->column; 
    
    if ((map->array[m_row][m_col - 1] == '-' && mirror->slash == 'f') || (map->array[m_row][m_col + 1] == '-' && mirror->slash == 'b'))
    {    
        if (mirror->slash == 'f')
        {
            map->array[m_row][m_col - 1] = ' ';
        }
        else
        {
            map->array[m_row][m_col + 1] = ' ';
        }

        while (map->array[m_row - 1][m_col] == ' ')
        {
            m_row -= 1;
            map->array[m_row][m_col] = '|';
            printMap(map, logs);
            map->array[m_row][m_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[m_row - 1][m_col] == map->array[player->row][player->column])
        {   
            map->array[player->row][player->column] = 'X';
        }
        else if (map->array[m_row - 1][m_col] == map->array[enemy->row][enemy->column])
        {
            map->array[enemy->row][enemy->column] = 'X';
        }
    }
    else if ((map->array[m_row][m_col + 1] == '-' && mirror->slash == 'f') || (map->array[m_row][m_col - 1] == '-' && mirror->slash == 'b'))
    {
        if (mirror->slash == 'f')
        {
            map->array[m_row][m_col + 1] = ' ';
        }
        else
        {
            map->array[m_row][m_col - 1] = ' ';
        }
        
        while (map->array[m_row + 1][m_col] == ' ')
        {
            m_row += 1;
            map->array[m_row][m_col] = '|';
            printMap(map, logs);
            map->array[m_row][m_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[m_row + 1][m_col] == map->array[player->row][player->column])
        {   
            map->array[player->row][player->column] = 'X';
        }
        else if (map->array[m_row + 1][m_col] == map->array[enemy->row][enemy->column])
        {
            map->array[enemy->row][enemy->column] = 'X';
        }
    }    
    else if ((map->array[m_row - 1][m_col] == '|' && mirror->slash == 'f') || (map->array[m_row + 1][m_col] == '|' && mirror->slash == 'b'))
    {
        if (mirror->slash == 'f')
        {
            map->array[m_row - 1][m_col] = ' ';
        }
        else
        {
            map->array[m_row + 1][m_col] = ' ';
        }

        while (map->array[m_row][m_col - 1] == ' ')
        {
            m_col -= 1;
            map->array[m_row][m_col] = '-';
            printMap(map, logs);
            map->array[m_row][m_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[m_row][m_col - 1] == map->array[player->row][player->column])
        {   
            map->array[player->row][player->column] = 'X';
        }
        else if (map->array[m_row][m_col - 1] == map->array[enemy->row][enemy->column])
        {
            map->array[enemy->row][enemy->column] = 'X';
        }
    }
    else if ((map->array[m_row + 1][m_col] == '|' && mirror->slash == 'f') || (map->array[m_row - 1][m_col] == '|' && mirror->slash == 'b'))
    {
        if (mirror->slash == 'f')
        {
            map->array[m_row + 1][m_col] = ' ';
        }
        else
        {
            map->array[m_row - 1][m_col] = ' ';
        }

        while (map->array[m_row][m_col + 1] == ' ')
        {
            m_col += 1;
            map->array[m_row][m_col] = '-';
            printMap(map, logs);
            map->array[m_row][m_col] = ' ';
            ucpSleep(0.10);
        }
        if (map->array[m_row][m_col + 1] == map->array[player->row][player->column])
        {   
            map->array[player->row][player->column] = 'X';
        }
        else if (map->array[m_row][m_col + 1] == map->array[enemy->row][enemy->column])
        {
            map->array[enemy->row][enemy->column] = 'X';
        }
    }
}