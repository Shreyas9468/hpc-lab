#include <omp.h>
#include <stdio.h>

int main() {
    int total_sum = 0;          // Variable to hold the total sum
    int num_threads = 4;        // Number of threads to be used
    int partial_sum = 0;        // Initialize partial sum for each thread

    // Parallel region
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();    // Get the thread ID
        int start = thread_id * 5 + 1;           // Determine start index for each thread
        int end = start + 4;                      // Determine end index for each thread
        int thread_partial_sum = 0;               // Initialize thread-specific partial sum

        // Ensure the end index does not exceed 20
        if (end > 20) {
            end = 20; // Cap end index at 20
        }

        // Loop through the assigned range and calculate the partial sum
        for (int i = start; i <= end; i++) {
            thread_partial_sum += i;
        }

        // Use a critical section to update total_sum safely
        #pragma omp critical
        {
            total_sum += thread_partial_sum;
        }

        // Print each thread's partial sum
        printf("Thread %d partial sum: %d\n", thread_id, thread_partial_sum);
    }

    // Final total sum is printed after the parallel region
    printf("Final total sum: %d\n", total_sum);
    return 0;
}
