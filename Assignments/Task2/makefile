#    Author: Kai-Yu Yu (90022616)
#    Date Modified: September 09, 2021
#    Purpose: This is the makefile for the laser tank game.

CC = gcc
CFLAGS = -Wall -Werror -g -ansi -std=c89
OBJ = main.o map.o ucpSleep.o structs.o tanks.o linked_list.o file_io.o
EXEC = laserTank

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c structs.h tanks.h map.h linked_list.h file_io.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c structs.h linked_list.h
	$(CC) $(CFLAGS) -c map.c

tanks.o: tanks.c structs.h ucpSleep.h map.h linked_list.h file_io.h
	$(CC) $(CFLAGS) -c tanks.c

structs.o: structs.c 
	$(CC) $(CFLAGS) -c structs.c

file_io.o: file_io.c linked_list.h structs.h
	$(CC) $(CFLAGS) -c file_io.c

linked_list.o: linked_list.c 
	$(CC) $(CFLAGS) -c linked_list.c

ucpSleep.o: ucpSleep.c
	$(CC) $(CFLAGS) -c ucpSleep.c

clean:
	rm -f $(EXEC) $(OBJ)
