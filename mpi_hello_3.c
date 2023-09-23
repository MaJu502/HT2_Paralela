/*
Autor: Marco Jurado 20308
Descripción: Este programa utiliza MPI para imprimir un mensaje
             desde cada proceso que se ejecuta en paralelo haciendo 
             uso de comm send y recv para pasar los mensajes.
*/
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    char message[100];
    char recv_message[100];
    
    if (rank == 0) {
        for (int sender = 1; sender < size; sender++) {
            MPI_Recv(recv_message, sizeof(recv_message), MPI_CHAR, sender, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 0 received a message from Process %d: %s\n", sender, recv_message);
            
            // Enviar confirmación de recepción
            sprintf(message, "Received by Process 0 from Process %d!", sender);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, sender, 1, MPI_COMM_WORLD);
        }
    } else {
        sprintf(message, "Hello from Process %d to Process 0!", rank);
        printf("Process %d sending a message to Process 0: %s\n", rank, message);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        
        // Recibir confirmación de recepción
        MPI_Recv(recv_message, sizeof(recv_message), MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received confirmation from Process 0: %s\n", rank, recv_message);
    }
    
    MPI_Finalize();
    
    return 0;
}
