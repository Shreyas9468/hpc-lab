#include <omp.h>
#include <stdio.h>

int main() {
    int total_sum = 0;
    int array[100];  // Example array
    for (int i = 0; i < 100; i++) array[i] = i + 1;

    #pragma omp parallel for
    for (int i = 0; i < 100; i++) {
        #pragma omp critical
        {
            total_sum += array[i];  // Critical section to avoid data race
        }
    }
    printf("Total sum with critical: %d\n", total_sum);

    total_sum = 0;  // Reset sum for atomic version

    #pragma omp parallel for
    for (int i = 0; i < 100; i++) {
        #pragma omp atomic
        total_sum += array[i];  // Atomic update
    }
    printf("Total sum with atomic: %d\n", total_sum);

    return 0;
}
