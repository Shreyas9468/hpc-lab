#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000  

int main() {
    double **A = (double **)malloc(SIZE * sizeof(double *));
    double **B = (double **)malloc(SIZE * sizeof(double *));
    double **C = (double **)malloc(SIZE * sizeof(double *));
    
    for (int i = 0; i < SIZE; i++) {
        A[i] = (double *)malloc(SIZE * sizeof(double));
        B[i] = (double *)malloc(SIZE * sizeof(double));
        C[i] = (double *)malloc(SIZE * sizeof(double));
    }

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;  
            B[i][j] = rand() % 10;
            C[i][j] = 0.0;  
        }
    }

    // Start the timer
    double start_time = omp_get_wtime();

    
    #pragma omp parallel for collapse(3)  
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Stop the timer
    double end_time = omp_get_wtime();
    printf("Time taken for matrix-matrix multiplication: %f seconds\n", end_time - start_time);

    
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
