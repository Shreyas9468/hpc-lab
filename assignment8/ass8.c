#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    
    int received_message;
    if (world_rank == 0) {
        MPI_Recv(&received_message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received message: %d\n", received_message);
        
        
        int message = 100;
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent message: %d\n", message);
    }

    if (world_rank == 1) {
        MPI_Recv(&received_message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message: %d\n", received_message);
        
        
        int message = 200;
        MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 sent message: %d\n", message);
    }

    MPI_Finalize();
    return 0;
}


// #include <mpi.h>
// #include <stdio.h>

// int main(int argc, char** argv) {
//     MPI_Init(&argc, &argv);

//     int world_rank;
//     MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

//     // Process 0 sends a message to Process 1
//     if (world_rank == 0) {
//         int message = 100;
//         MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
//         printf("Process 0 sent message: %d\n", message);

//         // Process 0 waits for a message from Process 1
//         int received_message;
//         MPI_Recv(&received_message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         printf("Process 0 received message: %d\n", received_message);
//     }

//     // Process 1 waits for a message from Process 0 before sending its own
//     if (world_rank == 1) {
//         int received_message;
//         MPI_Recv(&received_message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         printf("Process 1 received message: %d\n", received_message);

//         // Process 1 sends a message back to Process 0
//         int message = 200;
//         MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//         printf("Process 1 sent message: %d\n", message);
//     }

//     MPI_Finalize();
//     return 0;
// }
