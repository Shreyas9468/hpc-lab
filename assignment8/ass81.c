#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank; // Each process sends its rank
    int recv_data;

    // Send to the next process and receive from the previous process
    MPI_Send(&send_data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_data, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d sent %d and received %d\n", rank, send_data, recv_data);

    MPI_Finalize();
    return 0;
}
