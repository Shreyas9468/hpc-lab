#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Initialize the MPI environment

    int world_size; // Total number of processes
    int world_rank; // Rank of the current process

    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the current process

    int send_data = world_rank; // Each process sends its rank
    int recv_data; // Variable to store received data

    // Nearest neighbor exchange
    // Sending to the next neighbor
    int next_rank = (world_rank + 1) % world_size; // Next process in the ring
    int prev_rank = (world_rank - 1 + world_size) % world_size; // Previous process in the ring

    MPI_Send(&send_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD); // Send to the next process
    MPI_Recv(&recv_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Receive from the previous process

    // Output the results
    printf("Process %d sent %d to Process %d and received %d from Process %d\n",
           world_rank, send_data, next_rank, recv_data, prev_rank);

    MPI_Finalize(); // Clean up the MPI environment
    return 0;
}
