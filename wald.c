/*
	Use rejection sampling to draw random numbers from
	the Wald (Inverse Gaussian) distribution

	Wald distribution with parameters: 1.175, 0.1
	Proxy distribution is Exponential, parameter: .2
	The CDF of both these distributions looks similar,
	this was the criterion for the choice of the parameter in the exponential.
	Thus, with an M=2, the acceptance rate is close to 50%, theoretically

	The parameter for the Exponential distribution in the GSL is
	the inverse of the parameter in wikipedia or Mathematica
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define SQR(x)        ((x)*(x))

// Functions

double ran_wald_rejection(gsl_rng *rng, double mu, double theta);
double wald_pdf(double x, double mu, double theta);

// Global Variables

double pi;

int main()
{
	int i;
	int N=1000000000;

	double *x, mean,var;

	double mu=1.175;
	double theta=0.1;

	pi = 4.0*atan(1.0);

	x = (double*) malloc( N * sizeof(double) );

	// Mersenne Twister
	gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
	// Initialize the GSL generator with time:
    gsl_rng_set(rng, time(NULL)); // Seed with time

    for (i=0;i<N;++i)
    {
        x[i] = ran_wald_rejection(rng,mu,theta);
        //x[i] = gsl_ran_exponential(rng,mu);
    }

    mean = 0;
    for (i=0;i<N;++i)
    {
        mean += x[i];
        var  += SQR(x[i]);
    }
    mean = mean / N;
    
    var = 0;
    for (i=0;i<N;++i)
    {
        var  += SQR(x[i] - mean);
    }
    var  = sqrt( var / (N - 1.) );

    printf("Mean Num x Theo: %.8f %.8f\n",mean,mu);
    printf("Mean Num x Theo: %.8f %.8f\n",var,sqrt(pow(mu,3)/theta));

    printf("\n");

    gsl_rng_free(rng);
    free(x);

    return EXIT_SUCCESS;
}

double ran_wald_rejection(gsl_rng *rng, double mu, double theta)
{
	/*
		Sample from the Wald distribution (Inverse Gaussian), called f(x)
		using the rejection sampling algorithm, with the Exponential distribution as proxy, called g(y)

		Algorithm
		1. Sample y from g(y) and sample u uniformly from (0,1)
		2. Check whether u < f(y) / M g(y)
			If it is, accept y as a sample drawn from f
			It is is not, repeat 1
	*/
	double M,y,u,q,mie;
	extern double pi;

	M = 4.;
	mie= 5.; // shape parameter for the Exponential distribution
	u = 1.;
	q = 0.;
	while(u > q){
		y = gsl_ran_exponential(rng, mie);
		u = gsl_ran_flat(rng,0.,1.);
		q = wald_pdf(y,mu,theta) / M / gsl_ran_exponential_pdf(y,mie);
	}

	return y;
}

double wald_pdf(double x, double mu, double theta)
{
	extern double pi;
	// PDF of the Inverse Gaussian / Wald distribution
	return sqrt(theta/(2.*pi*x*SQR(x))) * exp(-theta*SQR(x-mu)/(2.*SQR(mu)*x));
}