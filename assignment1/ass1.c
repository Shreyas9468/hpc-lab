#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads;

    // Ask for the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Sequential Printing
    printf("\nSequential printing:\n");
    for(int i = 0; i < num_threads; i++) {
        printf("Hello, World\n");
    }

    // Parallel Printing using OpenMP
    printf("\nParallel printing:\n");
    #pragma omp parallel num_threads(num_threads)
    {
        printf("Hello, World from thread %d\n", omp_get_thread_num());
    }

    return 0;
}
