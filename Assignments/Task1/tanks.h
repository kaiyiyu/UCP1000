/*
    Author: Kai-Yu Yu (90022616)
    Date: August 14, 2021
    Purpose: This is the header file for the functions of the player and
    enemy tanks.
*/

char askCommand();
void movePlayer(char** map, int rows, int cols, int* p_row, int* p_col, int* e_row, int* e_col);
void initializePlayer(char** map, int* player_row, int* player_col, char* player_dir);
void initializeEnemy(char** map, int* enemy_row, int* enemy_col, char* enemy_dir);
int warnCollision();
void scanEnemyArea(char** map, int rows, int cols, int* p_row, int* p_col, int* e_row, int* e_col);