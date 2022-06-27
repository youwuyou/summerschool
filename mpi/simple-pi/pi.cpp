#include <cstdio>
#include <cmath>

constexpr int n = 840;

int main(int argc, char** argv)
// {

//   printf("Computing approximation to pi with N=%d\n", n);

//   int istart = 1;
//   int istop = n;

//   double pi = 0.0;
//   for (int i=istart; i <= istop; i++) {
//     double x = (i - 0.5) / n;
//     pi += 1.0 / (1.0 + x*x);
//   }

//   pi *= 4.0 / n;
//   printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);

// }
{   
  printf("Computing approximation to pi with N=%d\n", n);

  int istart = 1;
  int istop = n;

  // pi storing the final result
  double pi = 0.0;

  // STEP 0: obtain the rank number of the current process
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // STEP 1: divide the range in two
  if (rank == 0){
    // does i = 1, 2, ..., N/2
    istart = 1;
    istop = n / 2;
  }  
  else if (rank == 1){

   // does i = N/2 + 1, N/2 + 2, ...
    istart = n / 2 + 1;
    // istop = n;   => remains the same
  }
  
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi += 1.0 / (1.0 + x*x);
  }

  pi *= 4.0 / n;
  printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);

}