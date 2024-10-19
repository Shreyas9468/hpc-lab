#include <omp.h>
#include <stdio.h>
#include <time.h>

int main() {
    int array[1000];  // Large array
    for (int i = 0; i < 1000; i++) array[i] = i + 1;

    // Sequential sum
    int sequential_sum = 0;
    double start_time = omp_get_wtime(); // Start time for sequential sum
    for (int i = 0; i < 1000; i++)
        sequential_sum += array[i];
    double sequential_time = omp_get_wtime() - start_time; // Elapsed time for sequential sum
    printf("Sequential sum: %d, Time taken: %f seconds\n", sequential_sum, sequential_time);

    // Parallel sum using reduction
    int parallel_sum = 0;
    start_time = omp_get_wtime(); // Start time for parallel sum
    #pragma omp parallel for reduction(+:parallel_sum)
    for (int i = 0; i < 1000; i++)
        parallel_sum += array[i];
    double parallel_time = omp_get_wtime() - start_time; // Elapsed time for parallel sum

    printf("Parallel sum using reduction: %d, Time taken: %f seconds\n", parallel_sum, parallel_time);

    return 0;
}
