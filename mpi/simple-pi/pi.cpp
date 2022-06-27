#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;

int main(int argc, char** argv)
{ 

  int istart, istop;
  double pi = 0.0;
  double localpi = 0.;

  // STEP 0: obtain the rank number of the current process
  MPI_Init(&argc, &argv);

  int rank, ntasks;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);    // obtain rank
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);  // obtain size

  MPI_Status status;  

  
  // STEP 1: divide the range in two
  if (rank == 0){
    printf("Computing approximation to pi with N=%d\n", n);
    printf("Using %d MPI processes\n", ntasks);

    // does i = 1, 2, ..., N/2
    istart = 1;
    istop = n / 2;
  }  
  else if (rank == 1){
   // does i = N/2 + 1, N/2 + 2, ...
    istart = n / 2 + 1;
    istop = n;
  }

  // STEP 2: calculating the partial sum
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    localpi += 1.0 / (1.0 + x*x);
  }

  // STEP 3: communication
  if(rank == 1){
    // rank 1 sends partial sum to rank 0
    MPI_Send(&localpi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);

  }
  else if (rank == 0){

    pi = localpi;
    MPI_Recv(&localpi, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);

    // rank 0 calculates the final result
    // and prints out the result
    pi += localpi; 
    pi *= 4.0 / n;
    printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  }

   // Finalization
   MPI_Finalize();
}