#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 // Size of the array

int main(int argc, char** argv) {
    int rank, size;
    int A[N];
    int local_sum = 0;
    int global_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize the array only on process 0
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            A[i] = i + 1; // Fill array with values 1 to N
        }
    }

    // Broadcast the array to all processes
    MPI_Bcast(A, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process calculates the sum of half of the array
    int half = N / 2;
    if (rank == 0) {
        for (int i = 0; i < half; i++) {
            local_sum += A[i]; // P0 sums the first half
        }
    } else if (rank == 1) {
        for (int i = half; i < N; i++) {
            local_sum += A[i]; // P1 sums the second half
        }
    }

    // Reduce the local sums to get the global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 prints the final result
    if (rank == 0) {
        printf("Total Sum: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
