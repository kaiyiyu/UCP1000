#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

int main()
{
	int rows, columns;
	
	float** array = read_array(&rows, &columns);
	
	int i, j;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			printf("%f\n", array[i][j]);
	
		}
	}
	free(array);

	return 0;


}
