/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 09, 2021
    Purpose: This file handles all file IO in lasertank
*/

#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

/* Count lines in file to determine number of mirrors */
int countLines(char* filename)
{
    FILE* file;
    char c;
    int lines = 0;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("Error opening input file: ");
    }
    else if (ferror(file))
    {
        perror("Error reading input file: ");
    }
    else
    {
        for (c = getc(file); c != EOF; c = getc(file))
        {
            if (c == '\n') 
            {
                lines++;
            }
        }  
    }     
    fclose(file);

    return lines;
}

/* read through file again and check the validity of the inputs then update values by pointers */
int readFile(char* filename, int* mrow, int* mcol, int* prow, int* pcol, char* pdir, int* erow, int* ecol, char* edir, int row[], int col[], char dir[])
{
    FILE* file;
    file = fopen(filename, "r");

    int num_read;
    int index = 0;
    int done = 1;
    int line = 1;
    int error = 0;

    /* 0 for false then 1 for true */
    while (done)
    {
        if (line == 1)
        {
            num_read = fscanf(file, "%d %d\n", mrow, mcol);

            if (num_read != 2)
            {
                /* Incorrect number of values */
                printf("\e[1;31m!!! ERROR: Invalid number of values. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (*mrow < 5 || *mcol < 5 || *mrow > 25 || *mcol > 25)
            {
                printf("\e[1;31m!!! ERROR: Invalid border size. Values must be between 5 and 25. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else
            {
                line++;
            }
        }
        else if (line == 2)
        {
            num_read = fscanf(file, "%d %d %c\n", prow, pcol, pdir);

            if (num_read != 3)
            {
                printf("\e[1;31m!!! ERROR: Invalid number of values. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (*prow >= *mrow - 1 || *prow == 0 || *pcol >= *mcol - 1 || *pcol == 0)
            {
                printf("\e[1;31m!!! ERROR: Player tank coordinates overlap with map border. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (*pdir != 'n' && *pdir != 's' && *pdir != 'e' && *pdir != 'w')
            {
                printf("\e[1;31m!!! ERROR: Invalid player direction. Cannot initialize player tank. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else
            {
                line++;
            }
        }
        else if (line == 3)
        {
            num_read = fscanf(file, "%d %d %c\n", erow, ecol, edir);
            
            if (num_read != 3)
            {
                printf("\e[1;31m!!! ERROR: Invalid number of values. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (*erow >= *mrow - 1 || *erow == 0 || *ecol >= *mcol - 1 || *ecol == 0)
            {
                printf("\e[1;31m!!! ERROR: Enemy tank coordinates overlap with map border. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (*edir != 'n' && *edir != 's' && *edir != 'e' && *edir != 'w') 
            {
                printf("\e[1;31m!!! ERROR: Invalid player direction. Cannot initialize player tank. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else
            {
                line++;
            }
        }
        else if (line > 3)
        {
            num_read = fscanf(file, "%d %d %c\n", &row[index], &col[index], &dir[index]);
            
            if (num_read != 3)
            {
                printf("\e[1;31m!!! ERROR: Invalid number of values. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (row[index] >= *mrow - 1 || row[index] == 0 || col[index] >= *mcol - 1 || col[index] == 0)
            {
                printf("\e[1;31m!!! ERROR: Mirror coordinates overlap with map border. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else if (dir[index] != 'f' && dir[index] != 'b') 
            {
                printf("\e[1;31m!!! ERROR: Invalid mirror configuration. Cannot initialize mirror. !!!\e[0m\n");
                error++;
                done = 0;
            }
            else
            {
                index++;
                line++;
            }   
        }
        
        if (done)
        {
            done = !feof(file);
        }
    }
    fclose(file);

    return error;
}

/* Write each node/log to a file */
int writeFile(char* filename, LinkedList* logs, Map* map)
{    
    FILE* file;   
    ListNode* curr_node;          

    file = fopen(filename, "w");

    if(file == NULL)    
    {        
        perror("Error opening output file");            
    }      
    else    
    {   
        curr_node = logs->head;        
        while(curr_node != NULL)
        {
            fprintf(file, "%s\n", (char*)curr_node->value);
            fprintf(file, "\n%.*s\n\n", map->column, "=================");
            
            curr_node = curr_node->next;
        }
    }
    fclose(file);
    return 0;
}