#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_ellint.h>

// gsl documentation: https://www.gnu.org/software/gsl/doc/html/specfunc.html
// E[k] in GSL = E[k^2] in Mathematica

struct point
{
  double x,y;
};

int main(void) {

  struct point p[10];
  int i;
  
  for(i=0;i<10;i++){
    p[i].x = gsl_sf_ellint_Kcomp(i/10.,1e-9);
    p[i].y = gsl_sf_ellint_Ecomp(i/10.,1e-9);
  }

  for(i=0;i<10;i++){
    printf("%.9f ",p[i].x);
    printf("%.9f\n",p[i].y);
  }

  return 0;
}
