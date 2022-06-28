#include <stdio.h>
#include <mpi.h>
#include <vector>

int main(int argc, char **argv)
{
    int rank;
    int array[8][8];
    //TODO: Declare a variable storing the MPI datatype
    MPI_Datatype newtype;

    int i, j;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays
    if (rank == 0) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                array[i][j] = (i + 1) * 10 + j + 1;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                array[i][j] = 0;
            }
        }
    }

    if (rank == 0) {
        printf("Data in rank 0\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    //TODO: Create datatype
    int count, blocklen, stride;
    //int displs[];

    /*  A). sending col1
    count = 8 ; // number of blocks
    blocklen = 1; // number of elements in each block
    stride = 8;  //displacement between the blocks
    MPI_Type_vector(count, blocklen, stride, MPI_INT, &newtype);
    */
    


    MPI_Type_indexed();
    
    
    MPI_Type_commit(&newtype);

    //TODO: Send data
    if (rank == 0){
        // send the data
        /* a). send the col1 of the matrix "array"
        MPI_Send(&array[0][1], 1, newtype, 1, 1, MPI_COMM_WORLD);*/

        /* b). send the rows with displacement*/
        /* c). send a subarray */

    }
    else if (rank == 1){
        // receive the data
        // a). MPI_Recv(&array[0][1], 1, newtype, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }


    //TODO: Free datatype
    MPI_Type_free(&newtype);    

    // Print out the result on rank 1
    if (rank == 1) {
        printf("Received data\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}
