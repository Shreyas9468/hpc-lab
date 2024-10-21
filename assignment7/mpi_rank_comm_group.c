#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Step 1: Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Step 2: Get the total number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Step 3: Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Step 4: Check if the total number of processes is 5
    if (world_size != 5) {
        if (world_rank == 0) {
            printf("This program requires exactly 5 processes.\n");
        }
        MPI_Finalize(); // Clean up MPI environment
        return 1; // Exit if the number of processes is not 5
    }

    // Step 5: Display the rank and the communicator group
    printf("Hello from process %d out of %d processes!\n", world_rank, world_size);

    // Step 6: Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
