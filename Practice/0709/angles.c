/*Write a C Program to input two angles from user and find third angle of the triangle.*/

#include <stdio.h>
#define TOTAL_ANGLES 180

int calculateAngle(int first_angle, int second_angle); 

int main(void){

	int x, y;

	printf("Enter first two angles of a triangle: \n");
	scanf("%d", &x);
	scanf("%d", &y);

	printf("The value of the third angle is %d.\n", calculateAngle(x, y));
	
	return 0;
}

int calculateAngle(int first_angle, int second_angle) {

	int third_angle, sum_of_two_angles;

	sum_of_two_angles = first_angle + second_angle;
	third_angle = TOTAL_ANGLES - sum_of_two_angles;

	return third_angle;
}
