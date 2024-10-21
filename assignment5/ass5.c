#include <omp.h>
#include <stdio.h>

int main()
{

    char *family[] = {"Shreyas", "Pratima", "Mummy", "Pappa", "Didi"};
    int num_of_threads = 5;

#pragma omp parallel num_threads(num_of_threads) 
{
    int thread_id = omp_get_thread_num();
    if (thread_id < num_of_threads)
    {
        printf("Thread ID: %d - Family Member: %s\n", thread_id, family[thread_id]);
    }
}
return 0;
}