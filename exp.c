// https://lists.gnu.org/archive/html/help-gsl/2009-12/msg00031.html
#include <stdio.h>
#include <gsl/gsl_linalg.h>

int
main (void)
{
   double a[9] = {1,2,3,4,5,6,7,8,9};
   double b[9] = {0};

   gsl_matrix_view m
     = gsl_matrix_view_array(a, 3, 3);
   gsl_matrix_view em
     = gsl_matrix_view_array(b, 3, 3);

   gsl_linalg_exponential_ss(&m.matrix, &em.matrix, .01);

   gsl_matrix_fprintf(stdout, &em.matrix, "%g");

   return 0;
}