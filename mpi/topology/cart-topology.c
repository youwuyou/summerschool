#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

/*
Explore a Cartesian grid process topology by writing a toy program, where:

the MPI processes are arranged into a 2D Cartesian grid
every task prints out their linear rank together with its coordinates in the process grid
every task prints out the linear rank of their nearest neighboring processes

Run the code with both periodic and non-periodic boundaries, and experiment with the direction 
and displacement parameters of the MPI_Cart_shift routine.
*/




int main(int argc, char *argv[])
{
    int ntasks, my_id, irank;
    int dims[2];      /* Dimensions of the grid */
    int coords[2];    /* Coordinates in the grid */
    int neighbors[4]; /* Neighbors in 2D grid */
    int period[2] = {1, 1};
    MPI_Comm comm2d;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    /* Determine the process grid (dims[0] x dims[1] = ntasks) */
    if (ntasks < 16) {
        dims[0] = 2;
    } else if (ntasks >= 16 && ntasks < 64) {
        dims[0] = 4;
    } else if (ntasks >= 64 && ntasks < 256) {
        dims[0] = 8;
    } else {
        dims[0] = 16;
    }
    dims[1] = ntasks / dims[0];

    if (dims[0] * dims[1] != ntasks) {
        fprintf(stderr, "Incompatible dimensions: %i x %i != %i\n",
                dims[0], dims[1], ntasks);
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

// STEP 1: arrange the proccesses using Cartesian grid
    /* Create the 2D Cartesian communicator */
    /* TO DO */
    // old communicator == world
    // new communicator == cartesian communicator
    MPI_Cart_create(MPI_COMM_WORLD,
                    2,  // ndims
                    dims,
                    period,
                    1,
                    &comm2d
                    );

    /* Find out and store also the Cartesian coordinates of a rank */
    // i). cartesian communicator
    // ii). current rank
    // iii). length of the coord array
    // iv). coord array to be changed
    
    // STEP 2: prints out linear rank with its coordinates in grid for each process
    MPI_Comm_rank(comm2d, &my_id); // obtain rank in the new communicator
    MPI_Cart_coords(comm2d, my_id, 2, coords);

    
    // STEP 3: prints out linear rank of the nearest nerighbouring processes
    // STEP 3.1 Using enum for the direction
    enum DIRECTION{
        DOWN,
        UP,
        LEFT,
        RIGHT
    };

    // STEP 3.2 discover diff directions
    // MPI_Cart_shift(comm2d, direction, displ, &source, &dest);
    MPI_Cart_shift(comm2d, 0, 1, &neighbors[LEFT], &neighbors[RIGHT]);
    MPI_Cart_shift(comm2d, 1, 1, &neighbors[DOWN], &neighbors[UP]);

    for (irank = 0; irank < ntasks; irank++) {
        if (my_id == irank) {
            printf("rank: %3i, coord: (%2i %2i) neighbors=%3i, %3i, %3i, %3i\n",
                   my_id, coords[0], coords[1], neighbors[0], neighbors[1],
                   neighbors[2], neighbors[3]);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
