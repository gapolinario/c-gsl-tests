#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/*

    prints a list of numbers following a normal distribution
    inlining onl

*/

// global variables

double pi, sqrt2pi;

// functions
static inline void write( double *y, int N );
static inline double wavek( int j, int N, double L );


int main(){

    int i,N;
    double L,theta,abs_etak;
    extern double pi, sqrt2pi;
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937); // Mersenne Twister
    fftw_plan planf;
    double *etak;

    pi = atan2(0.,-1.); // which is fastest, this or 4.*atan(1.0) ?
    sqrt2pi = sqrt(2.0*pi);

    N=16384; // number of random numbers to be generated

    gsl_rng_set(rng,100); // seed for random numbers

    etak = (double *) fftw_malloc( N * sizeof(double) );

    for(i=1;i<N;i++){

        etak[i] = gsl_ran_gaussian( rng, 2. * pi ) ;

    }

    write(etak, N);

    fftw_destroy_plan( planf );
    gsl_rng_free( rng );
    fftw_free( etak );

    return 0;

}

static inline void write(double *y, int N)
/* writes vector y in binary to file fout */
{
        char name[60];
        FILE *fout;

        sprintf( name, "eta_real.dat" );

        fout = fopen(name,"w");

        fwrite(y, sizeof(y[0]), N, fout);

        fclose(fout);
}


static inline double wavek( int j, int N, double L )
{
    extern double pi;
    int s = k - N/2;

    return 2.*pi * (double)s / L
}