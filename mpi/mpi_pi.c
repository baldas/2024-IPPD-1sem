#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include <mpi.h>


int main(int argc, char* argv[]) {

  long i, count, n;
  double x,y,z,pi;
  double start, stop;
  int comm_sz, my_rank;
  

  if (argc < 2) {
    printf("Necessário informar um número N.\n");
    exit(-1);
  }
  n = strtoll(argv[1], NULL, 10);
  
  MPI_Init(&argc, &argv); 
   
   
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
  
  srand(my_rank);


  count = 0;

 // gettimeofday(&start, NULL);
  start = MPI_Wtime();
  for (i=0; i < n; ++i) {

    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;

    z = x * x + y * y;

    if( z <= 1 ) count++;
  }
  stop = MPI_Wtime();
  
  if (my_rank == 0) {

    long total_count = count;
    for (int q = 1; q < comm_sz; q++) {
      /* Receive message from process q */
      MPI_Recv(&count, 1, MPI_LONG, q,
            0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Received %ld from rank %d\n", count, q);
      total_count += count;
    } 

    pi = (double) total_count / n * 4 / comm_sz;
    printf(" Nossa estimativa de pi = %.14f\n", pi);
    printf("                     pi = %.14f\n", 4.0*atan(1.0));
   
    fprintf(stdout, "Tempo gasto: %g s\n", stop-start);
  }
  else {
    MPI_Send(&count, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD); 
  }
   
  MPI_Finalize(); 
  return(0);
}
