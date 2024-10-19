#include <omp.h>
#include <stdio.h>

int main() {
    int total_sum = 0;
    int num_threads = 4;  // Change as needed
    int partial_sum = 0;  // Declare partial_sum outside the parallel region

    // Parallel region
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_partial_sum = 0;  // Each thread's private partial sum

        // Parallel for loop to distribute iterations among threads
        #pragma omp for lastprivate(thread_partial_sum)
        for (int i = 1; i <= 20; i++) {
            thread_partial_sum += i;
        }

        // Use a critical section to update total_sum safely
        #pragma omp critical
        {
            total_sum += thread_partial_sum;
        }

        // Print each thread's partial sum
        printf("Thread %d partial sum: %d\n", omp_get_thread_num(), thread_partial_sum);
    }

    // Final total sum is printed after the parallel region
    printf("Final total sum: %d\n", total_sum);
    return 0;
}
