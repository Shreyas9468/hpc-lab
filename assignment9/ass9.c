#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Initialize the MPI environment

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of the current process

    int m = 5; 
    int n = 5; 

    int *A = NULL; 
    int *x = (int*)malloc(n * sizeof(int)); 
    int *local_A;  
    int local_m = m / world_size; 

    if (world_rank == 0) {
        // Initialize matrix A and vector x in process 0
        A = (int*)malloc(m * n * sizeof(int));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i * n + j] = i + j; // Fill matrix A with some values
            }
        }
        for (int i = 0; i < n; i++) {
            x[i] = i + 1; // Fill vector x with some values
        }
    }

    // Allocate memory for each process's subset of matrix rows
    local_A = (int*)malloc(local_m * n * sizeof(int));

    // Scatter rows of matrix A to all processes
    MPI_Scatter(A, local_m * n, MPI_INT, local_A, local_m * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast the vector x to all processes
    MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Local computation: multiply local rows of A with vector x
    int* local_y = (int*)malloc(local_m * sizeof(int)); // Local result vector
    for (int i = 0; i < local_m; i++) {
        local_y[i] = 0; // Initialize the result to 0
        for (int j = 0; j < n; j++) {
            local_y[i] += local_A[i * n + j] * x[j]; // Dot product of row i with vector x
        }
    }

    // Gather the results from all processes to process 0
    int* y = NULL;
    if (world_rank == 0) {
        y = (int*)malloc(m * sizeof(int)); // Final result vector in process 0
    }

    MPI_Gather(local_y, local_m, MPI_INT, y, local_m, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the result in process 0
    if (world_rank == 0) {
        printf("Resultant vector y = A * x:\n");
        for (int i = 0; i < m; i++) {
            printf("%d ", y[i]);
        }
        printf("\n");
    }

    // Free allocated memory
    free(local_A);
    free(local_y);
    free(x);
    if (world_rank == 0) {
        free(A);
        free(y);
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}
