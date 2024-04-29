
#include <stdio.h>
#include <mpi.h>


int main(int argc, char** argv) 
{
  int worldSize, myRank, aux, dest;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);


  MPI_Status st;
  if( myRank == 0 ) {
    MPI_Send((void*)&myRank, 1, MPI_INT, myRank+1, 0, MPI_COMM_WORLD);
    MPI_Recv(&aux, 1, MPI_INT, worldSize-1, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
  
    printf("Soma dos Ranks: %d\n", aux);
  }  else {
    int dest = (myRank == worldSize-1)?0:myRank+1;
    MPI_Recv(&aux,1,MPI_INT,myRank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
    aux += myRank;
    MPI_Send(&aux, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();

}

