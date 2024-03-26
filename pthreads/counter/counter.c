#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

volatile unsigned long counter=0;


int main()
{
  struct timeval start, stop;
 
  unsigned long limit = 0xFFFFFFFD;

  unsigned long i;

  gettimeofday(&start, NULL);


  for (i=0; i< limit; i++)
    counter++;

  gettimeofday(&stop, NULL);

  printf("counter = %lx\n", counter);
  double temp = \
               (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
                ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));
  printf("Time elapsed = %g ms\n", temp);

  return 0;
}
