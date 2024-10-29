#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100  

int main() {
    
    double **A = (double **)malloc(SIZE * sizeof(double *));
    double *x = (double *)malloc(SIZE * sizeof(double));
    double *y = (double *)malloc(SIZE * sizeof(double));

    for (int i = 0; i < SIZE; i++) {
        A[i] = (double *)malloc(SIZE * sizeof(double));
    }

    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;  
        }
        x[i] = rand() % 10;  
        y[i] = 0.0;  
    }

    
    double start_time = omp_get_wtime();

    
    #pragma omp parallel for  
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            y[i] += A[i][j] * x[j];  
        }
    }

    
    double end_time = omp_get_wtime();
    printf("Time taken for matrix-vector multiplication: %f seconds\n", end_time - start_time);

    
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}
