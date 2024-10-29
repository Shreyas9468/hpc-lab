#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); 

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 

    int m = 5; 
    int n = 5; 

    int *A = NULL; 
    int *x = (int*)malloc(n * sizeof(int)); 
    int *local_A;  
    int local_m = m / world_size; 

    if (world_rank == 0) {
       
        A = (int*)malloc(m * n * sizeof(int));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i * n + j] = i + j; 
            }
        }
        for (int i = 0; i < n; i++) {
            x[i] = i + 1; 
        }
    }

    local_A = (int*)malloc(local_m * n * sizeof(int));
    double start_time = MPI_Wtime();
    
    MPI_Scatter(A, local_m * n, MPI_INT, local_A, local_m * n, MPI_INT, 0, MPI_COMM_WORLD);

    
    MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);

    
    int* local_y = (int*)malloc(local_m * sizeof(int)); 
    for (int i = 0; i < local_m; i++) {
        local_y[i] = 0; 
        for (int j = 0; j < n; j++) {
            local_y[i] += local_A[i * n + j] * x[j]; 
        }
    }

    
    int* y = NULL;
    if (world_rank == 0) {
        y = (int*)malloc(m * sizeof(int)); 
    }

    MPI_Gather(local_y, local_m, MPI_INT, y, local_m, MPI_INT, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();
    if (world_rank == 0) {
        printf("Resultant vector y = A * x:\n");
        for (int i = 0; i < m; i++) {
            printf("%d ", y[i]);
        }
        printf("\n");
         printf("Total execution time with %d processes: %f seconds\n", world_size, end_time - start_time);
    
    }

    
    free(local_A);
    free(local_y);
    free(x);
    if (world_rank == 0) {
        free(A);
        free(y);
    }

    MPI_Finalize(); 
    return 0;
}
