#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>


void swap(int *a, int *b) {
	int temp=*a;
	*a=*b;
	*b=temp;
}

int pivot(int *array, int first, int last) {
	int p = first;
	int pivotElement = array[first];
	for(int i=first+1; i<=last; i++){
		if(array[i]<=pivotElement){
			p++;
			swap(&array[i],&array[p]);
		}
	}
	swap(&array[p],&array[first]);
	return p;
}

void quicksort(int *array, int first, int last) {
	int pivotElement;
	if(first < last) {
		pivotElement = pivot(array, first, last);
#pragma omp task
		quicksort(array, first, pivotElement-1);
#pragma omp task
		quicksort(array, pivotElement+1, last);
	}
}

int main(int argc, char *argv[])
{
  unsigned long i;
  unsigned long phase = 0;
  struct timeval start, stop;

  if (argc < 2) {
    printf("Precisa especificar o tamanho do vetor\n");
    exit(-1);
  }

  int length=atoi(argv[1]);
  int *vector = (int *)malloc(sizeof(int)*length);

  // inicializa vetor
  for (i=0; i<length; i++)
    vector[i] = rand()%24597 + 1;

  gettimeofday(&start, NULL);
  // Realiza a ordenacao

#pragma omp parallel
{ 
#pragma omp single
  quicksort(vector,0,length-1);
}

  gettimeofday(&stop, NULL);

  double tempo = \
    (((double)(stop.tv_sec)*1000.0 + (double)(stop.tv_usec/1000.0)) - \
    ((double)(start.tv_sec)*1000.0 + (double)(start.tv_usec/1000.0)));

  for (i=0; i<length-1; i++) {
    if (vector[i] > vector[i+1]) {
      fprintf(stdout, "Ooops, vetor não ordenado!\n");  
      break;
    }
  }

  fprintf(stdout, "Tempo total gasto = %g ms\n", tempo);

  return 0;
}
