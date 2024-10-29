#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4

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
        A = (int*)malloc(N * N * sizeof(int));
        C = (int*)malloc(N * N * sizeof(int));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i * N + j] = i + j;
                B[i * N + j] = i * j;
            }
        }
    }

    int* A_local = (int*)malloc(rows_per_proc * N * sizeof(int));
    int* C_local = (int*)malloc(rows_per_proc * N * sizeof(int));

    double start_time = MPI_Wtime();

    MPI_Scatter(A, rows_per_proc * N, MPI_INT, A_local, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    matrixMultiply(A_local, B, C_local, rows_per_proc, N);
    MPI_Gather(C_local, rows_per_proc * N, MPI_INT, C, rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Resulting Matrix C:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", C[i * N + j]);
            }
            printf("\n");
        }
        printf("Total execution time with %d processes: %f seconds\n", size, end_time - start_time);
    }

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
