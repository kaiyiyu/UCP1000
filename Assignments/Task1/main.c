/*
    Author: Kai-Yu Yu (90022616)
    Date: August 14, 2021
    Purpose: This file contains the main method that will
    run the laser tank game.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "tanks.h"

int main(int argc, char* argv[])
{   
    if (argc != 9)
    {
        printf("\e[1;31m!!! ERROR: Attempted to pass %d command line arguments. Please input 9 arguments to start the game. !!!\e[0m\n", argc);
        exit(-1);
    }

    /* Convert char* arguments into integers except for tank directions. */
    int row_size = atoi(argv[1]);
    int column_size = atoi(argv[2]);
    int player_row = atoi(argv[3]);
    int player_column = atoi(argv[4]);
    int enemy_row = atoi(argv[6]);
    int enemy_column = atoi(argv[7]);

    /* Create pointers to the integer variables to use throughout the program. */
    int* ptr_prow, *ptr_pcol, *ptr_erow, *ptr_ecol;
    ptr_prow = &player_row;
    ptr_pcol = &player_column;
    ptr_erow = &enemy_row;
    ptr_ecol = &enemy_column;
    
    /* Check the command line arguments for errors before allocating the 2D char array. */
    if (row_size < 5 || column_size < 5 || row_size > 25 || column_size > 25)
    {   /* Minimum (5) and maximum (25) values for rows and columns. */
        printf("\e[1;31m!!! ERROR: Invalid border size of %d by %d. Map size should be between 5 and 25 only. !!!\e[0m\n", row_size, column_size);
    }
    else if (player_row >= row_size - 1 || player_row == 0 || player_column >= column_size - 1 || player_column == 0)
    {   /* Coordinates of player tank must be within map boundary. */
        printf("\e[1;31m!!! ERROR: Player tank coordinates overlap with map border. Row should be between 0 and %d and column should be between 0 and %d. !!!\e[0m\n", row_size - 1, column_size - 1);
    }
    else if (strcmp(argv[5], "n") != 0 && strcmp(argv[5], "s") != 0 && strcmp(argv[5], "e") != 0 && strcmp(argv[5], "w") != 0)
    {   /* Direction must be either n, s, e, or w otherwise player won't initialize in map. */
        printf("\e[1;31m!!! ERROR: Invalid player direction. Cannot initialize player tank. !!!\e[0m\n");
    }
    else if (enemy_row >= row_size - 1 || enemy_row == 0 || enemy_column >= column_size - 1 || enemy_column == 0)
    {   /* Coordinates of enemy tank must be within map boundary. */
        printf("\e[1;31m!!! ERROR: Enemy tank coordinates overlap with map border. Row should be between 0 and %d and column should be between 0 and %d. !!!\e[0m\n", row_size - 1, column_size - 1);
    }
    else if (strcmp(argv[8], "n") != 0 && strcmp(argv[8], "s") != 0 && strcmp(argv[8], "e") != 0 && strcmp(argv[8], "w") != 0)
    {   /* Direction must be either n, s, e, or w otherwise enemy won't initialize in map. */
        printf("\e[1;31m!!! ERROR: Invalid enemy direction. Cannot initialize enemy tank. !!!\e[0m\n");
    }
    else 
    {   /* Only proceed when all arguments are valid. */
        
        /* Setup game map, player and enemy position by assigning to pointers. */
        char** map = createMap(row_size, column_size);
        initializePlayer(map, ptr_prow, ptr_pcol, argv[5]);
        initializeEnemy(map, ptr_erow, ptr_ecol, argv[8]);

        /* Loop through commands until enemy or player tank wins the game then free allocated array. */
        while (checkWin(map, row_size, column_size, ptr_prow, ptr_pcol, ptr_erow, ptr_ecol) == 0)
        {
            printMap(map, row_size, column_size);
            movePlayer(map, row_size, column_size, ptr_prow, ptr_pcol, ptr_erow, ptr_ecol);
            scanEnemyArea(map, row_size, column_size, ptr_prow, ptr_pcol, ptr_erow, ptr_ecol);
        }
        freeMap(map, row_size);
    }
   
    return 0;
}