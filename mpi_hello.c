/*
Autor: Marco Jurado 20308
Descripción: Este programa utiliza MPI para imprimir un mensaje
             desde cada proceso que se ejecuta en paralelo.
*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    // Inicializar MPI
    MPI_Init(&argc, &argv);
    
    // Comm rank con el id del proceso
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Comm size con número total de procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // IMensaje desde cada proceso
    printf("Hello World, I'm process %d of %d!\n", rank, size);
    
    // Finalizar MPI
    MPI_Finalize();
    
    return 0;
}
