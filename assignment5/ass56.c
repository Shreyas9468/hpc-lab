#include <omp.h>
#include <stdio.h>
#define N 1000000 
int arr[N]; 
void sumWithoutSync() {
    int total_sum = 0;
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        total_sum += arr[i]; // This will lead to a data race
    }
    
    printf("Total Sum without synchronization: %d\n", total_sum);
}

void sumWithCritical() {
    int total_sum = 0;
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical
        {
            total_sum += arr[i]; // Critical section ensures only one thread can modify total_sum at a time
        }
    }
    
    printf("Total Sum with critical section: %d\n", total_sum);
}

void sumWithAtomic() {
    int total_sum = 0;
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp atomic
        total_sum += arr[i]; // Atomic ensures the update is done safely without using full locks
    }
    
    printf("Total Sum with atomic: %d\n", total_sum);
}


int main() {

    for (int i = 0; i < 100; i++) arr[i] = i + 1;

    double stime = omp_get_wtime();
    sumWithoutSync();
    double etime = omp_get_wtime();
     printf("Time for unsynchronized version: %lf seconds\n", (etime - stime) );

       stime = omp_get_wtime();
    sumWithCritical();
     etime = omp_get_wtime();
     printf("Time for critical version: %lf seconds\n", (etime - stime) );

        stime = omp_get_wtime();
    sumWithAtomic();
     etime = omp_get_wtime();
     printf("Time for atomic version: %lf seconds\n", (etime - stime) );
    
}
