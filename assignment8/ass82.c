#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); 

    int world_size; 
    int world_rank; 

    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 

    int n = 10; 
    int *A = NULL; 

    
    if (world_rank == 0) {
        A = (int*)malloc(n * sizeof(int)); 
        for (int i = 0; i < n; i++) {
            A[i] = i + 1; 
        }
    }

    
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 

    
    int local_n = n / 2; 
    int *local_A = (int*)malloc(local_n * sizeof(int)); 

    
    MPI_Scatter(A, local_n, MPI_INT, local_A, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    
    int local_sum = 0;
    for (int i = 0; i < local_n; i++) {
        local_sum += local_A[i];
    }

    
    int total_sum = 0;
    if (world_rank == 0) {
        
        int sum_from_P1;
        MPI_Recv(&sum_from_P1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        
        total_sum = local_sum + sum_from_P1;

        
        free(A);
    } else if (world_rank == 1) {
        
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    
    if (world_rank == 0) {
        printf("Total sum of the array is: %d\n", total_sum);
    }

    
    free(local_A);

    MPI_Finalize(); 
    return 0;
}
