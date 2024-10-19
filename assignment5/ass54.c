#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000  // Matrix size

void matrix_multiply_serial(int **matA, int **matB, int **result) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
                result[i][j] += matA[i][k] * matB[k][j];
        }
}

void matrix_multiply_static(int **matA, int **matB, int **result) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
                result[i][j] += matA[i][k] * matB[k][j];
        }
}

void matrix_multiply_dynamic(int **matA, int **matB, int **result) {
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
                result[i][j] += matA[i][k] * matB[k][j];
        }
}

int main() {
    // Dynamically allocate matrices
    int **matA = malloc(N * sizeof(int *));
    int **matB = malloc(N * sizeof(int *));
    int **result = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matA[i] = malloc(N * sizeof(int));
        matB[i] = malloc(N * sizeof(int));
        result[i] = malloc(N * sizeof(int));
    }

    // Initialize matrices with random values
    srand(time(0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }

    // Measure time for serial
    double start_time = omp_get_wtime();
    matrix_multiply_serial(matA, matB, result);
    double serial_time = omp_get_wtime() - start_time;
    printf("Serial time: %f seconds\n", serial_time);

    // Measure time for static scheduling
    start_time = omp_get_wtime();
    matrix_multiply_static(matA, matB, result);
    double static_time = omp_get_wtime() - start_time;
    printf("Static scheduling time: %f seconds\n", static_time);

    // Measure time for dynamic scheduling
    start_time = omp_get_wtime();
    matrix_multiply_dynamic(matA, matB, result);
    double dynamic_time = omp_get_wtime() - start_time;
    printf("Dynamic scheduling time: %f seconds\n", dynamic_time);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(matA[i]);
        free(matB[i]);
        free(result[i]);
    }
    free(matA);
    free(matB);
    free(result);

    return 0;
}
