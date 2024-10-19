#include <omp.h>
#include <stdio.h>

int main() {
    int num_threads = 4;  // Change as required
    int sum_of_squares = 0;

    #pragma omp parallel num_threads(num_threads) reduction(+:sum_of_squares)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;
        printf("Thread ID: %d, Square: %d\n", thread_id, square);
        sum_of_squares += square;
    }

    printf("Sum of squares of thread IDs: %d\n", sum_of_squares);
    return 0;
}
