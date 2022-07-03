#include <cstdio>
#include <vector>
#include <mpi.h>

#define NTASKS 4

void print_buffers(int *printbuffer, int *sendbuffer, int buffersize);
void init_buffers(int *sendbuffer, int *recvbuffer, int buffersize);


int main(int argc, char *argv[])
{
    int ntasks, rank, color;
    std::vector<int> sendbuf(2 * NTASKS), recvbuf(2 * NTASKS);
    std::vector<int> printbuf(2 * NTASKS * NTASKS);

    MPI_Comm sub_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (ntasks != NTASKS) {
        if (rank == 0) {
            fprintf(stderr, "Run this program with %i tasks.\n", NTASKS);
        }
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    /* Initialize message buffers */
    init_buffers(sendbuf.data(), recvbuf.data(), 2 * NTASKS);

    /* Print data that will be sent */
    print_buffers(printbuf.data(), sendbuf.data(), 2 * NTASKS);

    /* TODO: use a single collective communication call (and maybe prepare
     *       some parameters for the call) */

    int root = 0;
    // Task 1: broadcast the data of process1 to all
    // MPI_Bcast(sendbuf.data(), 2 * NTASKS, MPI_INT, root, MPI_COMM_WORLD);
 
    // Task 2: scatter the data
    // MPI_Scatter(sendbuf.data(), 2, MPI_INT, recvbuf.data(), 2, MPI_INT, root, MPI_COMM_WORLD);

    // Task 3: gather vector
    // int revcounts[NTASKS] = {1, 1, 2, 4};
    // int displs[NTASKS] = { 0, 1, 2, 4};  // always at first place
    // MPI_Gatherv(sendbuf.data(), revcounts[rank], MPI_INT, recvbuf.data(), revcounts, displs, MPI_INT, 1, MPI_COMM_WORLD);
    
    // Task 4: all to all
    // from each process two are sent
    MPI_Alltoall(sendbuf.data(), 2, MPI_INT, recvbuf.data(), 2, MPI_INT, MPI_COMM_WORLD);

    /* Print data that was received */
    /* TODO: add correct buffer */
    // Task 1: sendbuf.data()
    //print_buffers(int *printbuffer, int *sendbuffer, int buffersize)

    // Task 2, 3, 4: recvbuf.data()
    print_buffers(printbuf.data(), recvbuf.data(), 2 * NTASKS);


    MPI_Finalize();
    return 0;
}


void init_buffers(int *sendbuffer, int *recvbuffer, int buffersize)
{
    int rank, i;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (i = 0; i < buffersize; i++) {
        recvbuffer[i] = -1;
        sendbuffer[i] = i + buffersize * rank;
    }
}


void print_buffers(int *printbuffer, int *sendbuffer, int buffersize)
{
    int i, j, rank, ntasks;

    MPI_Gather(sendbuffer, buffersize, MPI_INT,
               printbuffer, buffersize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    if (rank == 0) {
        for (j = 0; j < ntasks; j++) {
            printf("Task %i:", j);
            for (i = 0; i < buffersize; i++) {
                printf(" %2i", printbuffer[i + buffersize * j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
