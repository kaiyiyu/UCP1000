#include "arrays.h"
#include <stdlib.h>

int* createArray()
{
	int* numbers = malloc(ARRAY_LENGTH * sizeof(int));
	numbers[0] = 23;
	numbers[1] = 99;
	numbers[2] = 234;
	numbers[3] = 762;

	return numbers;
}

int sum(int* numbers, int count)
{
	int answer = 0;
	int i;
	for(i = 0; i < count; i++)
	{
	answer = answer + numbers[i];
	}

	return answer;
}
