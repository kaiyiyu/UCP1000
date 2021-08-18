CC = gcc
CFLAGS = -Wall -Werror -g  
OBJ = arrays.o main.o
EXEC = program

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c arrays.h 
	$(CC) $(CFLAGS) -c main.c

arrays.o: arrays.c arrays.h
	$(CC) $(CFLAGS) -c arrays.c

clean:
	rm -i $(OBJ) $(EXEC)
