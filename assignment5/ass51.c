// #include <omp.h>
// #include <stdio.h>

// int main() {
//     int num_threads = 4;  // Change as required
//     int sum_of_squares = 0;

//     #pragma omp parallel num_threads(num_threads) reduction(+:sum_of_squares)
//     {
//         int thread_id = omp_get_thread_num();
//         int square = thread_id * thread_id;
//         printf("Thread ID: %d, Square: %d\n", thread_id, square);
//         sum_of_squares += square;
//     }

//     printf("Sum of squares of thread IDs: %d\n", sum_of_squares);
//     return 0;
// }
#include<omp.h>
#include<stdio.h>

int main(){
    int sum_of_id =0;
    int num_thread=4;
    #pragma omp parallel num_threads(num_thread)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id*thread_id;
        sum_of_id += (square);
        printf("Thread id : %d , square of thread id : %d\n" , thread_id , square);
    }
    printf("Sum of Squers : %d\n " , sum_of_id);
}