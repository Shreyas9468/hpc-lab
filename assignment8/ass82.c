#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Initialize the MPI environment

    int world_size; // Total number of processes
    int world_rank; // Rank of the current process

    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the current process

    int n = 10; // Size of the array
    int *A = NULL; // Pointer to the array

    // Allocate and initialize the array only in process 0
    if (world_rank == 0) {
        A = (int*)malloc(n * sizeof(int)); // Allocate memory for the array
        for (int i = 0; i < n; i++) {
            A[i] = i + 1; // Initialize the array with values 1 to n
        }
    }

    // Broadcast the array size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 

    // Determine the number of elements to sum for each process
    int local_n = n / 2; // Each process sums half of the array
    int *local_A = (int*)malloc(local_n * sizeof(int)); // Local array for each process

    // Scatter the array to both processes
    MPI_Scatter(A, local_n, MPI_INT, local_A, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the local sum for each process
    int local_sum = 0;
    for (int i = 0; i < local_n; i++) {
        local_sum += local_A[i];
    }

    // Only process P0 will gather the result
    int total_sum = 0;
    if (world_rank == 0) {
        // Receive the local sum from P1
        int sum_from_P1;
        MPI_Recv(&sum_from_P1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Combine the sums
        total_sum = local_sum + sum_from_P1;

        // Free the allocated memory for the array
        free(A);
    } else if (world_rank == 1) {
        // Send the local sum to P0
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Process P0 prints the final result
    if (world_rank == 0) {
        printf("Total sum of the array is: %d\n", total_sum);
    }

    // Free local arrays
    free(local_A);

    MPI_Finalize(); // Clean up the MPI environment
    return 0;
}
