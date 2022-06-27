#include <cstdio>
#include <mpi.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    // TODO: say hello! in parallel
     // initialize
     MPI_Init(&argc, &argv);

    // obtain important information
     int rank, number_processes, namelen;
     char procname[MPI_MAX_PROCESSOR_NAME];

     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &number_processes);
     MPI_Get_processor_name(procname, &namelen);

     // rank
     if (rank == 0){
        std::cout << "Total processes " << number_processes << std::endl;
     }
     else {
         std::cout << "Hello world from processor " << procname <<
                                      " with rank " << rank << std::endl;
     } 

     // finalize
     MPI_Finalize();
}
