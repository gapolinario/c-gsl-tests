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

"omp parallel for" indeed makes some difference in running time,
but the details of the code (which does nothing) make -O3 serial run even faster

gcc vectorization-random.c -lm
time -p ./a.out
real 2.18
user 1.29
sys 0.88

gcc -O3 vectorization-random.c -lm
time -p ./a.out
real 0.00
user 0.00
sys 0.00

gcc -fopenmp vectorization-random.c -lm
time -p ./a.out
real 0.90
user 1.83
sys 1.34

gcc -O3 -fopenmp vectorization-random.c -lm
time -p ./a.out
real 0.64
user 0.65
sys 1.47

*/


int main(){

    const unsigned long int N = 268435456;
    unsigned long int i;
    double *m;
    double z;
    m = (double *) malloc( N * sizeof(double) );

    #pragma omp parallel for
    //#pragma omp simd
    for(i=0;i<N;i++){ m[i] = sqrt(0.13) ; }

    return 0;
}
