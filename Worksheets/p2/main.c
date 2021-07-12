#include <stdio.h>
#include "input.h"
#include "powers.h"

int main() {

	int number_of_powers = read_number();
	
	printf("The user inputted: %d\n", number_of_powers);

	int power;
	int i;

	for (i = 0; i < number_of_powers; i++)
	{
		power = next_power_of_two();
		printf("The next power is %d\n", power);
	}
		
	return 0;
	
}
