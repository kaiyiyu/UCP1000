cc = gcc
CFLAGS = -Wall -Werror -ansi 
OBJ = main.o syntax.o
EXEC = self_check

$(EXEC): $(OBJ)
	$(cc) $(OBJ) -o $(EXEC)

main.o: main.c syntax.h
	$(cc) $(CFLAGS) -c main.c

syntax.o: syntax.c
	$(cc) $(CFLAGS) -c syntax.c

clean:
	rm -i $(OBJ) $(EXEC)
