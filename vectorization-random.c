#include <stdlib.h>
#include <math.h>
#include <time.h>

/*

2^25 = 33554432
2^26 = 67108864
2^27 = 134217728
2^28 = 268435456

Assigning m[i] = sqrt(gsl_rng_uniform(rng)), there is barely no difference
between run times (with or without -O3, with our without -fopenmp)

Assigning m[i] = sqrt(time(NULL)), optimization even performs a little worse

*/


int main(){

    const unsigned long int N = 134217728;
    unsigned long int i;
    double *m;
    double z;
    m = (double *) malloc( N * sizeof(double) );

    #pragma omp simd
    for(i=0;i<N;i++){ m[i] = sqrt(0.13) ; }

    return 0;
}
