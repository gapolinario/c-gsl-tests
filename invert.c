/* A simple example of inverting a matrix using the gsl */
// https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_linalg.h>


gsl_matrix *invert_a_matrix(gsl_matrix *matrix);
void print_mat_contents(gsl_matrix *matrix);
void randomize_mat_contents(gsl_matrix *matrix);


static size_t size = 5;


        /************************************************************
         * PROCEDURE: invert_a_matrix
         * 
         * DESCRIPTION: Invert a matrix using GSL.
         *
         * RETURNS:
         *      gsl_matrix pointer
         */
gsl_matrix *
invert_a_matrix(gsl_matrix *matrix)
{
    gsl_permutation *p = gsl_permutation_alloc(size);
    int s;

    // Compute the LU decomposition of this matrix
    gsl_linalg_LU_decomp(matrix, p, &s);

    // Compute the  inverse of the LU decomposition
    gsl_matrix *inv = gsl_matrix_alloc(size, size);
    gsl_linalg_LU_invert(matrix, p, inv);

    gsl_permutation_free(p);

    return inv;
}


        /************************************************************
         * PROCEDURE: print_mat_contents
         * 
         * DESCRIPTION: Print the contents of a gsl-allocated matrix
         * 
         * RETURNS: 
         *      None.
         */
void
print_mat_contents(gsl_matrix *matrix)
{
    size_t i, j;
    double element;

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            element = gsl_matrix_get(matrix, i, j);
            printf("%f ", element);
        }
        printf("\n");
    }
}


        /************************************************************
         * PROCEDURE: randomize_mat_contents
         * 
         * DESCRIPTION: Overwrite entries in matrix with randomly
         *              generated values.
         *
         * RETURNS:
         *      None.
         */
void
randomize_mat_contents(gsl_matrix *matrix)
{
    size_t i, j;
    double random_value;
    double range = 1.0 * RAND_MAX;

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {

            // generate a random value
            random_value = rand() / range;
    
            // set entry at i, j to random_value
            gsl_matrix_set(matrix, i, j, random_value);

        }
    }
}


int
main(void)
{
    srand(time(NULL));

    gsl_matrix *mat = gsl_matrix_alloc(size, size);
    
    // fill this matrix with random doubles
    randomize_mat_contents(mat);

    // let's see the original now
    printf("Original matrix:\n");
    print_mat_contents(mat);

    printf("\n");

    // compute the matrix inverse
    gsl_matrix *inverse = invert_a_matrix(mat);
    printf("Inverted matrix:\n");
    print_mat_contents(inverse);

    printf("\n");

    // first argument is input, second is output
    gsl_linalg_exponential_ss(inverse,inverse,.01);

    printf("Exponentiated matrix:\n");
    print_mat_contents(inverse);

    gsl_matrix_free(mat);
    gsl_matrix_free(inverse);

    return 0;
}
