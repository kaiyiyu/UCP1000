#include <stdio.h>

int main(void) {

	int first_number, second_number;

	printf("Enter two integers: \n");
	scanf("%d", &first_number);
	scanf("%d", &second_number);

	if (first_number % second_number == 0) {
		printf("%d is divisible by %d.\n", first_number, second_number);
	} else {
		printf("%d is not divisible by %d.\n", first_number, second_number);
	}

	return 0;

}
