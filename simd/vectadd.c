
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 150000000
 
int a[N], b[N], c[N];

int main()
{
  volatile int i;
  int n=N;
  struct timeval start, stop;

  gettimeofday(&start, NULL);
  
  #pragma omp simd
  for (i=0; i<n; i++)
    a[i] = b[i] + c[i] ;
  
  gettimeofday(&stop, NULL);


  double temp = \
    (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
    ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));

  fprintf(stdout, "Time elapsed = %g ms\n", temp);

  return 0;
}
