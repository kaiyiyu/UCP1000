/*
    Author: Kai-Yu Yu (90022616)
    Date Modified: September 12, 2021
    Purpose: This is the header file for the functions of the tanks, lasers, and mirrors.
*/

#ifndef TANKS_H
#define TANKS_H

#include "structs.h"
#include "linked_list.h"

/* Tanks */
char askCommand();
void movePlayer(Map* map, Tanks* player, Tanks* enemy, LinkedList* logs, char* filename);
void initializePlayer(Map* map, Tanks* player);
void initializeEnemy(Map* map, Tanks* enemy);
int warnCollision();
void scanEnemyArea(Map* map, Tanks* player, Tanks* enemy, LinkedList* logs);

/* Laser Movement */
void shootLaser(Map* map, Tanks* shooter, Tanks* opponent, LinkedList* logs);
void deflectLaser(Map* map, Mirrors* mirror, Tanks* player, Tanks* enemy, LinkedList* logs);

#endif