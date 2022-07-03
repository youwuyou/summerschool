#include <cstdio>
#include <cmath>
#include <mpi.h>

constexpr int n = 840;

int main(int argc, char*argv[])
{
  MPI_Init(&argc, &argv);

  // obtain important information
  int myid, ntasks;
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

  printf("Computing approximation to pi with N=%d\n", n);

  // bounds of calculation
  // int istart = 1;
  // int istop = n;
  int length = n / ntasks;
  int istart = myid * length + 1;
  int istop = (myid + 1) * length;

  double pi_array[ntasks];

  // calculation of the pi
  double partial_pi = 0.;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    partial_pi += 1.0 / (1.0 + x*x);
  }

  // using collective operations
  int root = 0;
  MPI_Gather(&partial_pi, 1, MPI_DOUBLE, 
             &pi_array, ntasks, MPI_DOUBLE, root, MPI_COMM_WORLD);
  
  MPI_Barrier(MPI_COMM_WORLD);

  if (myid == 0){
      double pi = 0.;
      for (int i = 0; i < ntasks; ++i){
          pi += pi_array[i];
      }
      pi *= 4. / n;
      printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  }
  // final calculation
  // pi *= 4.0 / n;
  // printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);


  MPI_Finalize();

}
   

