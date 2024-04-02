#include <stdlib.h>
#include <stdio.h>
#include <omp.h>



int main(int argc, char *argv[])
{

#pragma omp parallel
{
  int my_id = omp_get_thread_num();
  int threads = omp_get_num_threads();

  fprintf(stdout, "Hello from thread %d (total of %d threads)\n", my_id, threads);
}
 
  return 0;
}



