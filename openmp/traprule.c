#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

double f(double x)
{
  return pow(x,10)+pow(x,3)+63;
}

int main()
{
  double a=1, b=500;
  int n=100000000;
  double h = (b-a)/n;
  struct timeval start, stop;
  int i;

  gettimeofday(&start, NULL);
 
  double approx = (f(a) + f(b)) / 2.0;

#pragma omp parallel for default(none) shared(n, a, h) reduction(+:approx)
  for (i=1; i<=n-1; i++) {
    approx += f(a + i*h);
  }
  
  approx = h*approx;


  gettimeofday(&stop, NULL);
  
  double tempo = \
    (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
    ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));

  fprintf(stdout, "Area do trapezio = %g\n", approx);
  fprintf(stdout, "Tempo total gasto = %g ms\n", tempo);

  return 0;
}
