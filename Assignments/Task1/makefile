#    Author: Kai-Yu Yu (90022616)
#    Date: August 14, 2021
#    Purpose: This is the makefile for the laser tank game.

CC = gcc
CFLAGS = -Wall -Werror -g
OBJ = main.o map.o tanks.o laser.o ucpSleep.o
EXEC = laserTank

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c map.h tanks.h 
	$(CC) $(CFLAGS) -c main.c

map.o: map.c
	$(CC) $(CFLAGS) -c map.c

tanks.o: tanks.c ucpSleep.h laser.h
	$(CC) $(CFLAGS) -c tanks.c

laser.o: laser.c map.h ucpSleep.h
	$(CC) $(CFLAGS) -c laser.c

ucpSleep.o: ucpSleep.c
	$(CC) $(CFLAGS) -c ucpSleep.c

clean:
	rm -f $(EXEC) $(OBJ)
