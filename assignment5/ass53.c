#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0; // Final sum to be computed
    int partial_sum = 0; // Each thread's partial sum
    int num_thread = 10;

    #pragma omp parallel num_threads(num_thread) 
    {   partial_sum =0;
        int thread_id = omp_get_thread_num();
        #pragma omp for lastprivate(partial_sum)
        for (int i = 1; i <= 20; i++) {
            partial_sum += i; 
        }
         sum = partial_sum;

        printf("The value of Sum : %d for thread id : %d\n" , partial_sum,thread_id);
    }
    

    // The last thread's partial sum is assigned to the final sum
   

    printf("The sum of the first 20 natural numbers is: %d\n", sum);
    return 0;
}