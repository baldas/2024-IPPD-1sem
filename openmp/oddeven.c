#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define N 200000

int vector[N];

int main()
{
  unsigned long i;
  unsigned long phase = 0;
  struct timeval start, stop;

  // inicializa vetor
  for (i=0; i<N; i++)
    vector[i] = N-i;

  gettimeofday(&start, NULL);
  
  // Realiza a ordenacao
  // odd even sort algorithm
  for (phase=0; phase<N; phase++) {

  {
      if (phase%2 == 0) {
#pragma omp parallel for default(none) shared(vector)	    
      for (i=1; i<N; i += 2) {
          if (vector[i-1] > vector[i]) {
            int tmp = vector[i-1];
            vector[i-1] = vector[i];
            vector[i] = tmp;
          }
      }
    }
    else 
    {
#pragma omp parallel for default(none) shared(vector)	    
      for (i=2; i<N; i += 2) {
          if (vector[i-1] > vector[i]) {
            int tmp = vector[i-1];
            vector[i-1] = vector[i];
            vector[i] = tmp;
          }
      }
    }
  }  // bloco paralelo
}


  gettimeofday(&stop, NULL);

  double tempo = \
    (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
    ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));

  for (i=0; i<N-1; i++) {
    if (vector[i] > vector[i+1]) {
      fprintf(stdout, "Ooops, vetor não ordenado!\n");  
      break;
    }
  }

  fprintf(stdout, "Tempo total gasto = %g ms\n", tempo);

  return 0;
}
