#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_matrix.h>

#define wavek(j) 2.*pi*((j)-N/2)/L

/*
    Improvements
    1. Probably the Gaussian correlation matrix has an exact, analytical Cholesky decomposition
    2. GSL matrix get, is it as efficient as storing directly?
*/

// global variables

double pi, sqrt2pi;

// functions
double chi_r(double x);
static inline void write(double *y, int N);

int main(){

    int i,j,N;
    extern double pi, sqrt2pi;
    double L, dx;
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937); // Mersenne Twister
    double *zed, *eta;

    printf("OK");
    
    pi = atan2(0.,-1.); // which is fastest, this or 4.*atan(1.0) ?
    sqrt2pi = sqrt(2.0*pi);

    N=8; // number of random numbers to be generated
    L=2.*pi;
    dx = L/(double)N;

    gsl_rng_set(rng,200); // seed for random numbers

    gsl_matrix * sigma = gsl_matrix_alloc (N, N); // Correlation Matrix
    zed = (double *) malloc( N * sizeof(double) ); // Independent noise
    eta = (double *) malloc( N * sizeof(double) ); // Noise

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            gsl_matrix_set (sigma, i, j, chi_r((i-j)*dx) );
        }
    }

    printf("Assignment OK");

    gsl_linalg_cholesky_decomp1(sigma);

    printf("Cholesky OK");

    for(i=0;i<N;i==0){ zed[i] = gsl_ran_gaussian( rng, 1.0 ); }

    for(i=0;i<N;i++){
        eta[i] = 0;
        for(j=0;j<i+1;j++){
            eta[i] += gsl_matrix_get(sigma, i, j) * zed[j];
        }
    }

    write(eta, N);

    gsl_rng_free( rng );
    gsl_matrix_free( sigma );
    free( zed );
    free( eta );

    return 0;

}

double chi_r(double x)
{
    return exp(-.5*x*x);
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

static inline void cholesky_decomp( double *y, )
/*
    Cholesky decomposition of matrix y stored in row-major order
    as a vector.

    Q: Can the output be written over the input? Probably
*/
{
    
}