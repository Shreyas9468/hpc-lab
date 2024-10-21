#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000  // Size of the matrix and vector

int main() {
    // Allocate memory for matrix A and vector x, result vector y
    double **A = (double **)malloc(SIZE * sizeof(double *));
    double *x = (double *)malloc(SIZE * sizeof(double));
    double *y = (double *)malloc(SIZE * sizeof(double));

    for (int i = 0; i < SIZE; i++) {
        A[i] = (double *)malloc(SIZE * sizeof(double));
    }

    // Initialize matrix A and vector x with random values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;  // Random values between 0 and 9
        }
        x[i] = rand() % 10;  // Random values for vector x
        y[i] = 0.0;  // Initialize result vector y to zero
    }

    // Start the timer
    double start_time = omp_get_wtime();

    // Matrix-vector multiplication using OpenMP
    #pragma omp parallel for  // Parallelize the outer loop
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            y[i] += A[i][j] * x[j];  // y[i] = A[i] * x
        }
    }

    // Stop the timer
    double end_time = omp_get_wtime();
    printf("Time taken for matrix-vector multiplication: %f seconds\n", end_time - start_time);

    // Free allocated memory
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}
