/*

 Generates a random number with the stdlib.
 The time lib can also be used to define the seed,
 simply uncomment the respective lines

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <time.h>

int main(){

	int N;
	float L,pi;

	pi = atan2(0.,-1.);

	N=1024;
	L=2.*pi;

	//srandom(time(NULL));
	srandom(100); // seed for random numbers

	L = (float) random() / (float) RAND_MAX ;

	printf("%f\n",L);

	return 0;

}