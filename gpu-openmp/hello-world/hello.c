#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

/*
  Task 1: compile without offloading support
    - with only -mp option
    - run the code in a GPU node

  Task 2: with offloading
    - with -mp=gpu -gpu=cc70
    - 


*/



int main()
{
  int num_devices = omp_get_num_devices();
  printf("Number of available devices %d\n", num_devices);

#pragma omp target
  {
    if (omp_is_initial_device()) {
      printf("Running on host\n");
    } else {
      printf("Running on device\n");
    }
  }

}
