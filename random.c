#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/*
with the great help of:
https://gist.github.com/PhDP/2366579
*/

int main(int argc, const char *argv[])
{
	int i;
	// Mersenne Twister
	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
	// Taus2
	//gsl_rng *rng = gsl_rng_alloc(gsl_rng_taus2);
    // Initialize the GSL generator with time:
    gsl_rng_set(rng, time(NULL)); // Seed with time

    printf ("generator type: %s\n", gsl_rng_name (rng)); // generator
    
    // Get uniform numbers
    printf("Uniform random numbers:\n   ");
    for (i = 0; i < 10; ++i)
    {
        printf("%.4f ", gsl_ran_gaussian_ziggurat(rng, 1.0));
    }
    printf("\n");

    // Get binomial:
    printf("Binomial with n = 100 and p = 0.1:\n   ");
    for (i = 0; i < 10; ++i)
    {
        printf("%u ", gsl_ran_binomial(rng, 0.1, 100));
    }
    printf("\n");

    gsl_rng_free(rng);

    return EXIT_SUCCESS;
}
