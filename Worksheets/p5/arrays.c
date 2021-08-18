#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

float** read_array(int* rows, int* columns)
{
	FILE* data_file = fopen("data.txt", "r");

	fscanf(data_file, "%d %d", rows, columns);

	float** array = malloc(*rows*sizeof(float*));
	int i, j;

	for(i = 0; i < *rows; i++)
	{
		array[i] = malloc(*columns*sizeof(float));
	}
	printf("Number of rowns %d\nNumber of columns %d\n", *rows, *columns);
	
	for(i = 0; i < *rows; i++)
	{
		for(j = 0; j < *columns; j++)
		{
			fscanf(data_file, "%f", &array[i][j]);
		}
	}

	fscanf(data_file, "%f", &array[0][0]);
	
	fclose(data_file);

	return array;
}
