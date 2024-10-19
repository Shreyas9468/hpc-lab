#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100  // Size of the matrices

void matrix_multiply(int matA[N][N], int matB[N][N], int result[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0; // Initialize the result matrix element
            for (int k = 0; k < N; k++) {
                result[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

int main() {
    int matA[N][N], matB[N][N], result[N][N];

    // Initialize matrices with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matA[i][j] = rand() % 10; // Random values between 0 and 9
            matB[i][j] = rand() % 10;
        }
    }

    double start_time = omp_get_wtime(); // Start timing
    matrix_multiply(matA, matB, result);
    double end_time = omp_get_wtime(); // End timing

    printf("Matrix-Matrix Multiplication completed in %f seconds.\n", end_time - start_time);

    return 0;
}
