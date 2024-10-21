#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4  

// Function to multiply local rows of A with matrix B
void matrixMultiply(int* A_local, int* B, int* C_local, int rows_per_proc, int n) {
    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < n; j++) {
            C_local[i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                C_local[i * n + j] += A_local[i * n + k] * B[k * n + j];
            }
        }
    }
}

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = N / size;
    int* A = NULL;
    int* B = (int*)malloc(N * N * sizeof(int));
    int* C = NULL;

    if (rank == 0) {
        // Initialize matrices A and B (only in root process)
        A = (int*)malloc(N * N * sizeof(int));
        C = (int*)malloc(N * N * sizeof(int));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i * N + j] = i + j;
                B[i * N + j] = i * j;
            }
        }
    }

    // Allocate memory for local matrices (for each process)
    int* A_local = (int*)malloc(rows_per_proc * N * sizeof(int));
    int* C_local = (int*)malloc(rows_per_proc * N * sizeof(int));

    // Scatter rows of matrix A to all processes
    MPI_Scatter(A, rows_per_proc * N, MPI_INT, A_local, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast matrix B to all processes
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local matrix multiplication
    matrixMultiply(A_local, B, C_local, rows_per_proc, N);

    // Gather the result from all processes to the root process
    MPI_Gather(C_local, rows_per_proc * N, MPI_INT, C, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Print result (only in root process)
    if (rank == 0) {
        printf("Resulting Matrix C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i * N + j]);
            }
            printf("\n");
        }
    }

    // Free allocated memory
    free(A_local);
    free(C_local);
    free(B);
    if (rank == 0) {
        free(A);
        free(C);
    }

    MPI_Finalize();
    return 0;
}
