#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, tag = 0;
    double start_time, end_time, elapsed_time;
    int data = 42;
    int recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        printf("This program requires exactly 2 MPI processes, but you are running with %d.\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Sendrecv(&data, 1, MPI_INT, 1, tag, &recv_data, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        end_time = MPI_Wtime();
        elapsed_time = end_time - start_time;
        printf("Elapsed time: %f seconds\n", elapsed_time);
    } else {
        MPI_Sendrecv(&data, 1, MPI_INT, 0, tag, &recv_data, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Finalize();
    return 0;
}
