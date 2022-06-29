#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mpi.h>

#define DATASIZE   64
#define WRITER_ID   0

void single_reader(int, int *, int);
void ordered_print(int, int, int *, int);

int main(int argc, char *argv[])
{
    int my_id, ntasks, localsize;
    int *localvector;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if (ntasks > 64) {
        fprintf(stderr, "Datasize (64) should be divisible by number "
                "of tasks.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (DATASIZE % ntasks != 0) {
        fprintf(stderr, "Datasize (64) should be divisible by number "
                "of tasks.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    localsize = DATASIZE / ntasks;
    localvector = (int *) malloc(localsize * sizeof(int));

    single_reader(my_id, localvector, localsize);

    ordered_print(ntasks, my_id, localvector, localsize);

    free(localvector);

    MPI_Finalize();
    return 0;
}

void single_reader(int my_id, int *localvector, int localsize)
{
    FILE *fp;
    int *fullvector, nread;
    char const *fname = "output.txt";

    /* TODO: Implement a function that will read the data from a file so that
       a single process does the file io. Use rank WRITER_ID as the io rank */
    
    // allocate space
    fullvector = (int*)malloc(DATASIZE * sizeof(int));
    
    if(my_id == WRITER_ID){

        fp = fopen(fname, "rb");
        if (fp == NULL){
            // exception handling
            fprintf(stderr, "Error: %d (%s)\n", errno, strerror(errno));
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        else{
            // read the data from the file
            fread(fullvector, sizeof(int), DATASIZE, fp);
            fclose(fp);
            printf("Read %d elements from the file output.txt", DATASIZE);
        }
    }

    // MPI Scatter
    MPI_Scatter(fullvector, localsize, MPI_INT, localvector, localsize, MPI_INT, 0, MPI_COMM_WORLD);


    free(fullvector);
}

/* Try to avoid this type of pattern when ever possible.
   Here we are using this serialized output just to make the
   debugging easier. */
void ordered_print(int ntasks, int rank, int *buffer, int n)
{
    int task, i;

    for (task = 0; task < ntasks; task++) {
        if (rank == task) {
            printf("Task %i received:", rank);
            for (i = 0; i < n; i++) {
                printf(" %2i", buffer[i]);
            }
            printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
}
