#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank (process ID) of the current process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the size of the communicator (number of processes)
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check if we have exactly 5 processes
    if (size != 5) {
        if (rank == 0) {
            printf("Please run the program with exactly 5 processes.\n");
        }
        MPI_Finalize();
        return -1;
    }

    // Each process prints its rank and the communicator size
    printf("Process %d out of %d processes in MPI_COMM_WORLD\n", rank, size);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
