#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank (process ID) of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print a hello message from each process
    printf("Hello from process %d out of %d processes\n", rank, size);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
