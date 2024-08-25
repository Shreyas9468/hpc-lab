#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void res(int n, int threads) {
    // Vector scalar addition
    double scaler = 6.9;
    double *a = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        a[i] = i % 16;
    }

    // Set the number of threads
    omp_set_num_threads(threads);

    // Measure time
    double start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        a[i] += scaler;
    }
    double end_time = omp_get_wtime();

    // Print the results
    printf("Time taken for size: %d with %d threads: %f seconds\n", n, threads, end_time - start_time);
    free(a);
}

int main() {
    // Use a larger vector size to better observe performance differences
    int vector_size = 10000000;  

    // Running with different numbers of threads
    res(vector_size, 6);
    res(vector_size, 5);
    res(vector_size, 4);
    res(vector_size, 3);

    return 0;
}
