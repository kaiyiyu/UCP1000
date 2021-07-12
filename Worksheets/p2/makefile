cc = gcc
CFLAGS = -Wall -Werror -ansi 
OBJ = input.o main.o powers.o
EXEC = powers_of_two

$(EXEC): $(OBJ)
	$(cc) $(OBJ) -o $(EXEC)

main.o: main.c input.h powers.h
	$(cc) $(CFLAGS) -c main.c

powers.o: powers.c
	$(cc) $(CFLAGS) -c powers.c

input.o: input.c
	$(cc) $(CFLAGS) -c input.c

clean:
	rm -i $(OBJ) $(EXEC)
