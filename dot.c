#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define SQ(x) (x)*(x)

struct point
{
  double x,y;
};

double dot_product(struct point a, struct point b);

int main(void) {

  struct point aa, bb;
  struct point *xyv;
  int i, nt, im, ip;
  double d1;
  double *dlist;

  nt = 4;

  xyv = (struct point *) malloc(nt * sizeof(struct point));
  dlist = (double *) malloc(nt * sizeof(double));

  xyv[0].x = .52;
  xyv[0].y = .59;
  xyv[1].x = .76;
  xyv[1].y = .62;
  xyv[2].x = .10;
  xyv[2].y = .77;
  xyv[3].x = .76;
  xyv[3].y = .14;

  for(i=0;i<nt;i++){

      im=((i-1+nt)%nt);
      ip=((i+1)%nt);

      printf("%d %d %d\n",i,im,ip);

      //fazendo o produto escalar
      aa.x=(xyv[ip].x-xyv[i].x);
      aa.y=(xyv[ip].y-xyv[i].y);
      bb.x=(xyv[im].x-xyv[i].x);
      bb.y=(xyv[im].y-xyv[i].y);

      d1 = .5 * sqrt(dot_product(aa,aa));
      d1 += .5 * sqrt(dot_product(bb,bb));

      dlist[i] = d1;

  }//fim do loop sobre q

  for(i=0;i<nt;i++){
    printf("%.6f\n",dlist[i]);
  }

  free(xyv);
  free(dlist);

  return 0;
}

// produto escalar de dois vetores bidimensionais
double dot_product(struct point a, struct point b){
    int i;
    double d;
    d = a.x * b.x + a.y * b.y;
    return d;
}
