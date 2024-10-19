#include <omp.h>
#include <stdio.h>

int main() {
    int Aryabhatta = 10;  // Declare the variable in the outer scope

    // Parallel region with private copies of Aryabhatta for each thread
    #pragma omp parallel private(Aryabhatta)
    {
        int thread_id = omp_get_thread_num();
        Aryabhatta = 10;  // Initialize the private variable inside the parallel region
        int result = thread_id * Aryabhatta;
        printf("Thread ID: %d, Multiplication Result: %d\n", thread_id, result);
    }

    return 0;
}
