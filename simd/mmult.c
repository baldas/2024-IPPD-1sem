#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

// parâmetro de linha de comando: <tamanho>
int main(int argc, char *argv[])
{

	struct timeval start, end; //gettimeofday
	double t, sum;
	int i, j, k, tam;
   
  if (argc < 2) {
    printf("É necessário especificar o tamanho da matriz\n");
    exit(-1);
  }
  
  srand(0);

	tam = atoi(argv[1]);

	// Aloca espaço dinâmico para as matrizes
	double **ma = (double **)malloc(tam * sizeof(double*));
	for (int i = 0; i < tam; i++) 
			ma[i] = (double *)malloc(tam * sizeof(double));

	double **mb = (double **)malloc(tam * sizeof(double*));
	for (int i = 0; i < tam; i++) 
			mb[i] = (double *)malloc(tam * sizeof(double));

	double **mfim = (double **)malloc(tam * sizeof(double*));
	for (int i = 0; i < tam; i++) 
			mfim[i] = (double *)malloc(tam * sizeof(double));

	if (ma == NULL || mb == NULL || mfim == NULL)
    {
        fprintf(stderr, "Out of memory");
        exit(-1);
    }

	// Preenche as matrizes com valores randômicos
	for (i=0;i<tam;i++)
		for (j=0;j<tam;j++){
			ma[i][j] = (fmod (rand(), 50.111));
			mb[i][j] = (fmod (rand(), 50.111));
		}
	
		
	// a multiplicação
	gettimeofday(&start, NULL);
#pragma omp parallel for simd
	for (i=0; i<tam; i++)
		for (j=0; j<tam; j++)
			for (k=0; k<tam; k++)
				mfim[i][j] += ma[i][k] * mb[k][j];

	gettimeofday(&end, NULL);


	t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000.0;
	
	printf("Tempo gasto: %f\n", t);

  /* imprime matriz resultante no stderr */
/*  
	for (i=0; i<tam; i++)
		for (j=0; j<tam; j++)
      fprintf(stderr, "%g ", mfim[i][j]);
*/

	free(ma); 
  free(mb); 
  free(mfim);
	
	return 0;
}

