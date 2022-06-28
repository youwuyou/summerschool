#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <iostream>


int main(int argc, char *argv[])
{
  int n=1000, cnt=3, reps=10000;

  typedef struct {
    float coords[3];   // float - 4 byte
    int charge;        // int   - 4 byte
    char label[2];     // char  - 1 byte
  } particle;

  particle particles[n]; // 1000 particles

  int i, j, myid, ntasks;
  double t1, t2;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  /* fill in some values for the particles */
  if (myid == 0) {
    for (i=0; i < n; i++) {
      for (j=0; j < 3; j++)
        particles[i].coords[j] = (float)rand()/(float)RAND_MAX*10.0;
      particles[i].charge = 54;
      strcpy(particles[i].label, "H");
    }
  }

  // TODO: define data type for the struct
  MPI_Datatype particletype, temptype;
  MPI_Aint disp[cnt], dist[2], lb, extent;


  // i). sending a single struct object
  MPI_Datatype types[cnt] = { MPI_FLOAT, MPI_INT, MPI_CHAR};
  int blocklen[cnt] = {3, 1, 2};  // lengths of blocks
  
  // determining displacements
  MPI_Get_address(&particles[0].coords, &disp[0]);
  MPI_Get_address(&particles[0].charge, &disp[1]);
  MPI_Get_address(&particles[0].label, &disp[2]);

  // make displacements relative
  disp[2] -= disp[0];
  disp[1] -= disp[0];
  disp[0] = 0;

  MPI_Type_create_struct(cnt, blocklen, disp, types, &particletype);
  MPI_Type_commit(&particletype);

  // TODO: check extent (not really necessary on most platforms) 
  // uses MPI_get_extent for checking
  MPI_Type_get_extent(particletype, &lb, &extent);
  MPI_Get_address(&particles[0], &dist[0]);
  MPI_Get_address(&particles[1], &dist[1]);

  if(extent!= dist[1] - dist[0]){
      temptype = particletype;
      lb = 0;
      extent = disp[1] - disp[0];

      MPI_Type_create_resized(temptype, lb, extent, &particletype);
      MPI_Type_commit(&particletype);
      MPI_Type_free(&temptype);
  }


  // communicate using the created particletype
  t1 = MPI_Wtime();
  if (myid == 0) {
    for (i=0; i < reps; i++) // multiple sends for better timing
      // TODO: send
      // i <-> tag
      MPI_Send(particles, n, particletype, 1, i, MPI_COMM_WORLD);
      std::cout << "Sent data from process of rank "<< myid << std::endl;

  } else if (myid == 1) {
    for (i=0; i < reps; i++)
      // TODO: receive
      MPI_Recv(particles, n, particletype, 0, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      std::cout << "Received data from process of rank "<< myid << std::endl;
  }
  MPI_Type_free(&particletype);   // free the new type

  // TODOs end
  t2 = MPI_Wtime();

  printf("Time: %i, %e \n", myid, (t2-t1)/(double)reps);
  printf("Check: %i: %s %f %f %f \n", myid, particles[n-1].label,
          particles[n-1].coords[0], particles[n-1].coords[1],
          particles[n-1].coords[2]);

  MPI_Finalize();
  return 0;
}
