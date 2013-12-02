#include <stdio.h>
#include <assert.h>

//declare functions:
double calc_throw();

//main function:
int main () {

	float v_0;
	float t;
	const float  g = 9.82;


	printf("v_0:");
	scanf("%f", &v_0);

	printf("t:");
	scanf("%f", &t);

	printf("\nwill use v_0=%f and t=%f\n", v_0, t);

	calc_throw(v_0, t, g);

	return 0;
}


//calculate throw:
double calc_throw (float v_0, float t, float g) {

       	float v = v_0 + g * t;
	float s = v * t;

	printf("v: %f\ns: %f\ng: %f\n", v, s, g);

        return 0;

}

