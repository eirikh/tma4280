// this give us access to the MPI library
#include <mpi.h>

// for printing etc
#include <stdio.h>

int main(int argc, char** argv)
{
  // Initialize MPI
  MPI_Init(&argc, &argv);

  int size, rank;

  // Figure out the number of processes and our rank
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (size != 2) {
    printf("Need exactly two processes\n");
    MPI_Finalize();
    return 1;
  }

  int payload;

  if (rank == 0) {
    // determine rank of receiver
    int sendrank = 1;

    // Send data to other process
    MPI_Send(&rank, 1, MPI_INT, sendrank, 0, MPI_COMM_WORLD);

    // Receive from the other process 
    int recvrank = 1;

    MPI_Status status;
    MPI_Recv(&payload, 1, MPI_INT, recvrank, 0, MPI_COMM_WORLD, &status);
  } else {
    // determine rank of receiver
    int sendrank = 0;

    // Send data to other process
    MPI_Send(&rank, 1, MPI_INT, sendrank, 0, MPI_COMM_WORLD);

    // Receive from the other process 
    int recvrank = 0;

    MPI_Status status;
    MPI_Recv(&payload, 1, MPI_INT, recvrank, 0, MPI_COMM_WORLD, &status);
  }

  // print to tty
  printf("process %i: received %i\n", rank, payload);

  // close down MPI
  MPI_Finalize();

  // ay-oh-kay
  return 0;
}