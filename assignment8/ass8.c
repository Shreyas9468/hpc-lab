#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        printf("This program requires exactly two processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int message = rank; // Each process sends its rank
    // Deadlock situation
    MPI_Send(&message, 1, MPI_INT, (rank + 1) % 2, 0, MPI_COMM_WORLD);
    MPI_Recv(&message, 1, MPI_INT, (rank + 1) % 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received message %d\n", rank, message);

    MPI_Finalize();
    return 0;
}
