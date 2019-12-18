#include <stdlib.h>

/*

A test for SIMD pragmas (CPU vectorization). In the end, the efficiency of vectorization could not
be verified in this case, since the code is very simple, compiling with

gcc vectorization-test.c

or

gcc vectorization-test.c -fopenmp

did not make much difference, and the openmp code was slightly slower because it had to launch
the parallel threads. But optimization made a huge difference, running N = 2^28 = 268,435,456,
without optimization (above), times were:

real    0m1.097s
user	0m0.696s
sys	0m0.400s

while, with -O3 optimization (with or without openmp, makes no difference), times were

real	0m0.003s
user	0m0.000s
sys	0m0.003s

*/


int main(){

    const unsigned long int N = 268435456;
    unsigned long int i;
    double *m;
    double z;
    m = (double *) malloc( N * sizeof(double) );

    #pragma omp simd
    for(i=0;i<N;i++){ m[i] = .013 ; }

    return 0;
}
