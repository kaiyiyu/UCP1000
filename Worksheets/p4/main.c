#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

int main(int argc, char* argv[])
{
	printf("This program will make an array and find the sum of all numbers\n");

	int* numbers = createArray();

	int i;
	for (i = 0; i < ARRAY_LENGTH; i++)
	{
		printf("The number %d is %d\n", i+1, numbers[i]);
	}

	printf("The sum of all numbers is %d\n", sum(numbers, ARRAY_LENGTH));
	
	free(numbers);
	return 0;
}
