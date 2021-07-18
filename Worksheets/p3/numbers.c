#include <stdio.h>
#include "order.h"
#include <stdlib.h>


int main()
{
	int* a = malloc(sizeof(int));
	int* b = malloc(sizeof(int));

	 *a = 20;
	 *b = 2;

	printf("BEFORE: a = %d and b = %d\n", *a, *b);

	ascending2(a, b);

	printf("AFTER: a = %d and b = %d\n", *a, *b);
	
	free(a);
	free(b);
	return 0; 



}
