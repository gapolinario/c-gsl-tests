#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#define wavek(j) 2.*pi*((j)-N/2)/L

/*

    what still needs to be done:
    understand complex fourier transforms and see if they are needed,
    then use this knowledge to declare plans correctly
    write output as binary file
    read binary file and test its statistics in the most simple manner with Mathematica

    important to remark: inlining only happens with optimization

    Real chi is real and even, chir[j] = chir[N-j], because it only makes sense for
    a correlation function. Hence, chik is purely real. 

    1st test:
    Compute Chi(l*dx), calculate its forward Fourier transform, compare with Mathematica output

*/

// global variables

double pi, sqrt2pi;

// functions
double chi_r(double x);
static inline void write(double *y, int N);

int main(){

    int i,N;
    double L,theta,abs_etak,dx,tmp;
    extern double pi, sqrt2pi;
    gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937); // Mersenne Twister
    fftw_plan planf, planb;
    double *etak, *chik;

    pi = atan2(0.,-1.); // which is fastest, this or 4.*atan(1.0) ?
    sqrt2pi = sqrt(2.0*pi);

    N=1024; // number of random numbers to be generated
    L=2.*pi;
    dx = L/(double)N;

    gsl_rng_set(rng,200); // seed for random numbers

    etak = (double *) fftw_malloc( N * sizeof(double) );
    chik = (double *) fftw_malloc( N * sizeof(double) );
    //etar = (double *) fftw_malloc( N * sizeof(double) );

    planf = fftw_plan_r2r_1d( N, chik, chik, FFTW_R2HC, FFTW_ESTIMATE );
    planb = fftw_plan_r2r_1d( N, etak, etak, FFTW_HC2R, FFTW_ESTIMATE );

    for(i=0;i<N;i++){ chik[i] = chi_r(-.5*L+i*dx); }

    // is this transform HC to R as well? or R to HC? I'm still confused as hell
    // but a little less confused than yesterday
    // after transform chik holds numerical fourier tranform of chi_l = chi(dx*l)
    fftw_execute(planf);

    // assign half-complex eta
    // eta[0] and eta[N/2]: imaginary part is zero
    // N must be even
    // etak is half-complex, first half holds the real componets, second half holds the imaginary components

    etak[0] = gsl_ran_gaussian( rng, fabs(chik[0]) );
    etak[N/2] = gsl_ran_gaussian( rng, fabs(chik[N/2]) );
    for(i=1;i<N/2;i++){

        abs_etak = gsl_ran_gaussian( rng, fabs( chik[i] ) );

        etak[i] = abs_etak * gsl_rng_uniform( rng ) / sqrt(2); // real part
        etak[N-i] = abs_etak * gsl_rng_uniform( rng ) / sqrt(2);
        //etak[N-i] = 0; // imag part

    }
/*
    etak[0] = gsl_ran_gaussian( rng, sqrt(fabs(chik[0])) );
    etak[N/2] = gsl_ran_gaussian( rng, sqrt(fabs(chik[N/2])) );
    for(i=0;i<N/2+1;i++){

        theta = gsl_rng_uniform( rng );
        abs_etak = gsl_ran_gaussian( rng, sqrt(fabs( chik[i] )) );

        etak[i] = abs_etak * cos( theta );
        etak[N-i] = abs_etak * sin( theta );

    }
*/
    fftw_execute(planb);

    write(etak, N);

    fftw_destroy_plan( planf );
    fftw_destroy_plan( planb );
    gsl_rng_free( rng );
    fftw_free( etak );
    fftw_free( chik );

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