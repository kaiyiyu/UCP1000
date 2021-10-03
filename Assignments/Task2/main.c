/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This file contains the main method that will
    run the laser tank game.
*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "linked_list.h"
#include "tanks.h"
#include "map.h"
#include "file_io.h"

int main(int argc, char* argv[])
{   
    if (argc != 3)
    {
        printf("\e[1;31m!!! ERROR: Attempted to pass %d command line arguments. Please input 3 arguments to start the game. !!!\e[0m\n", argc);
        exit(-1);
    }
    
    /* initial values */
    int m_row, m_col, p_row, p_col, e_row, e_col, count;
    char p_dir, e_dir;
    
    int* mrow_ptr = &m_row;
    int* mcol_ptr = &m_col;
    int* prow_ptr = &p_row;
    int* pcol_ptr = &p_col;
    int* erow_ptr = &e_row;
    int* ecol_ptr = &e_col;
    char* pdir_ptr = &p_dir;
    char* edir_ptr = &e_dir;

    count = countLines(argv[1]);

    int mirror_count = count - 3;
    
    /* array to store mirror values +1 so not invalid if no mirrors */
    int row[mirror_count + 1];
    int col[mirror_count + 1];
    char dir[mirror_count + 1];

    int error;
    error = readFile(argv[1], mrow_ptr, mcol_ptr, prow_ptr, pcol_ptr, pdir_ptr, erow_ptr, ecol_ptr, edir_ptr, row, col, dir);
  
    if (error != 0)
    {
        printf("\e[1;31mInvalid input in given file. Please try again.\e[0m\n");
    }
    else
    {
        /* only allocate when all conditions are met */
        Map* map = createMapStruct(m_row, m_col);
        Tanks* player = createPlayerStruct(p_row, p_col, p_dir);
        Tanks* enemy = createEnemyStruct(e_row, e_col, e_dir);
    
        /* +1 for valid array but no allocation */
        Mirrors* mirror[mirror_count + 1];

        LinkedList* logs = createLinkedList();

        /* Only allocate for each mirror struct if there are mirror configurations in file */
        if (mirror_count != 0)
        {
            int i;    
            for (i = 0; i < mirror_count; i++)
            {
                mirror[i] = (Mirrors*)malloc(sizeof(Mirrors));
                createMirrorStruct(mirror[i], row[i], col[i], dir[i]);
            }    
        }

        /* setup lasertank game */
        map->array = createMap(map);
        initializeMirrors(map, mirror, mirror_count);
        initializePlayer(map, player);
        initializeEnemy(map, enemy);

        /* loop through commands until winner is determined */
        int i;
        while (checkWin(map, player, enemy, logs) == 0)
        {
            printMap(map, logs);
            movePlayer(map, player, enemy, logs, argv[2]);
            
            if (mirror_count != 0)
            {
                for (i = 0; i < mirror_count; i++)
                {
                    deflectLaser(map, mirror[i], player, enemy, logs);
                }
            }
            
            scanEnemyArea(map, player, enemy, logs);
        }
        /* write log to file then proceed to heap freeing */
        writeFile(argv[2], logs, map);

        freeMap(map);
        freeStructs(map, player, enemy, mirror, mirror_count);
        freeLinkedList(logs);
    }
    return 0;
}