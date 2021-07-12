int next_power_of_two()
{
	static int power_of_two = 1;
	power_of_two *= 2;

	return power_of_two;

	}
