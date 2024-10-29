#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); 

    int world_size; 
    int world_rank; 

    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 

    int send_data = world_rank; 
    int recv_data; 

    
    
    int next_rank = (world_rank + 1) % world_size; 
    int prev_rank = (world_rank - 1 + world_size) % world_size; 

    MPI_Send(&send_data, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD); 
    MPI_Recv(&recv_data, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

    
    printf("Process %d sent %d to Process %d and received %d from Process %d\n",
           world_rank, send_data, next_rank, recv_data, prev_rank);

    MPI_Finalize(); 
    return 0;
}
