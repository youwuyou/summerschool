#include <cstdio>
#include <vector>
#include <mpi.h>
#include <iostream>


/*  NEW KNOWLEDGE
i). 
int MPI_Get_count(const MPI_Status *status,   -> return status of receive operation (Status)
                      MPI_Datatype datatype,  -> datatype of each receive buffer element (handle)
                               int *count
                )

ii). using std::vector<T> for the message storage and receive buffer
     NOTE:  size needs to be specified => definition needed
            - MPI_Send  <-> uses a small message size
            - MPI_Recv  <-> uses the array size in the call as predefined

iii). using data() method to pass the pointer

iv).  using MPI_Get_count to obtain the number of elements received
     NOTE:      needed to pass the status by reference
                specifying the type as eg. MPI_INT necessary
                passes some empty int variable for storing the count number
*/


int main(int argc, char *argv[])
{
    int myid, ntasks;
    constexpr int arraysize = 100000;
    constexpr int msgsize = 100000;
    std::vector<int> message(arraysize);
    std::vector<int> receiveBuffer(arraysize);
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Initialize message
    for (int i = 0; i < arraysize; i++) {
        message[i] = myid;
    }

    // TODO: Implement sending and receiving as defined in the assignment
    // Send msgsize elements from the array "message", and receive into 
    // "receiveBuffer"
   
    if (myid == 0) {
        MPI_Send(message.data(), msgsize, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(receiveBuffer.data(), arraysize, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        
        // declare variable for counting
        int nrecv;
        MPI_Get_count(&status, MPI_INT, &nrecv);

        printf("Rank %i received %i elements, first %i\n", myid, nrecv, receiveBuffer[0]);
    } else if (myid == 1) {

        MPI_Recv(receiveBuffer.data(), arraysize, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Send(message.data(), msgsize, MPI_INT, 0, 0, MPI_COMM_WORLD);
        
        int nrecv;
        MPI_Get_count(&status, MPI_INT, &nrecv);
        
        printf("Rank %i received %i elements, first %i\n", myid, nrecv, receiveBuffer[0]);
    }

    MPI_Finalize();
    return 0;
}
