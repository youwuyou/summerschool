#include <cstdio>
#include <mpi.h>



int main(int argc, char *argv[])
{
    // TODO: say hello! in parallel
     // initialize
     MPI_Init(NULL, NULL);

     // get numbers i). no processes and 
     // ii). rank
     int rank;
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    
     // rank
     std::cout << "Hello world from processor with rank " << rank << std::endl;
 
     // finalize
     MPI_Finalize();
}
