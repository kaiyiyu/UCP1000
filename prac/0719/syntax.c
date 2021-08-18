/* Calculate and display the difference of two input values */

#include <stdio.h>

int calc_sum() 
{
	int X, x, sum; 
	
	scanf("%d%d", &X, &x); 
	sum = X + x;
	printf("%d + %d = %d\n", X, x, sum); 
	
	return 0;
}
