/*
    Author: Kai-Yu Yu (90022616)
    Date: August 14, 2021
    Purpose: This is the header file for the functions of the game map.
*/

char** createMap(int rows, int columns);
void printMap(char** map, int rows, int columns);
int checkWin(char** map, int rows, int cols, int* p_row, int* p_col, int* e_row, int* e_col);
void freeMap(char** map, int rows);