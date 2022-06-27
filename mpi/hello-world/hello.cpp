#include <cstdio>
#include <mpi.h>
#include <iostream>


int main(int argc, char *argv[])
{
    // TODO: say hello! in parallel
     // initialize
     MPI_Init(NULL, NULL);

     // get numbers 
     // i). no processes and 
     // ii). rank
     int rank;
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

     int number_processes;
     MPI_Comm_size(MPI_COMM_WORLD, &number_processes);
    
     // rank
     if (rank == 0){
        std::cout << "Hello world from process with rank " << rank << std::endl;
        std::cout << "Total processes " << number_processes << std::endl;
     }
     else {
         std::cout << "Hello world from process with rank " << rank << std::endl;
     } 

     // finalize
     MPI_Finalize();
}
