#include <stdio.h>

int factorial(int n);

int main(void) {

	int n;

	printf("Enter a number: \n");
	scanf("%d", &n);

	while (n >= 0) {
		printf("Factorial of %d = %d\n", n, factorial(n));
		printf("Enter another number: \n");
		scanf("%d", &n);
	}

	printf("Invalid input. %d is a negative integer.\n", n);

	return 0;
}

int factorial(int n) {
		
	int i, j = 1;

	for (i = 1; i <= n; i++)
		j *= i;

	return j;

}
