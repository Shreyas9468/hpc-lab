#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100  // Size of the matrix and vector

void matrix_vector_multiply(int mat[N][N], int vec[N], int result[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        result[i] = 0; // Initialize the result vector element
        for (int j = 0; j < N; j++) {
            result[i] += mat[i][j] * vec[j];
        }
    }
}

int main() {
    int mat[N][N], vec[N], result[N];

    // Initialize the matrix with random values and the vector
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 10; // Random values between 0 and 9
        }
        vec[i] = rand() % 10; // Random values for the vector
    }

    double start_time = omp_get_wtime(); // Start timing
    matrix_vector_multiply(mat, vec, result);
    double end_time = omp_get_wtime(); // End timing

    printf("Matrix-Vector Multiplication completed in %f seconds.\n", end_time - start_time);

    return 0;
}
