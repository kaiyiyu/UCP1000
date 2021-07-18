cc = gcc
CFLAGS= -Wall -Werror
OBJ = order.o numbers.o

EXEC= numbers_swapping 

$(EXEC): $(OBJ)
	$(cc) $(OBJ) -o $(EXEC)

order.o: order.c order.h
	$(cc) $(CFLAGS) -c order.c

numbers.o: numbers.c order.h
	$(cc) $(CFLAGS) -c numbers.c


clean:
	rm -i $(EXEC) $(OBJ)

