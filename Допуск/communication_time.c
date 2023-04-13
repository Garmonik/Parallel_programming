#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int const size = 550000;

int main(int argc, char **argv){
	int rank;
	double mass[size];

	int BUFSIZE = sizeof (double) * size + MPI_BSEND_OVERHEAD; 
	char *buf;
	MPI_Status status;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	if (rank == 0){
		double time_s, time;
		time_s = MPI_Wtime ();
		MPI_Rsend (&mass[0], size, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
		MPI_Recv (&mass[0], size, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD, &status);
		time = (MPI_Wtime() - time_s) / 2;
		printf ("process %d, time = %f\n", rank, time);
		MPI_Recv (&mass[0], size, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD, &status);
		MPI_Rsend (&mass[0], size, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
	}
    
	if (rank == 1){
		MPI_Recv (&mass[0], size, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &status);
		MPI_Rsend (&mass[0], size, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);

		double time_s, time;

		time_s = MPI_Wtime ();

		MPI_Rsend (&mass[0], size, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
		MPI_Recv (&mass[0], size, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &status);

		time = (MPI_Wtime () - time_s) / 2;
		
		printf ("process %d, time = %f\n", rank, time);
	}
	if (rank == 0){
		double time_s, time;
		time_s = MPI_Wtime ();
		MPI_Rsend (&mass[0], size, MPI_DOUBLE, 2, 5, MPI_COMM_WORLD);
		MPI_Recv (&mass[0], size, MPI_DOUBLE, 2, 5, MPI_COMM_WORLD, &status);
		time = (MPI_Wtime() - time_s) / 2;
		printf ("process %d, time = %f\n", rank, time);
		MPI_Recv (&mass[0], size, MPI_DOUBLE, 2, 5, MPI_COMM_WORLD, &status);
		MPI_Rsend (&mass[0], size, MPI_DOUBLE, 2, 5, MPI_COMM_WORLD);
	}
	MPI_Finalize ();

	return 0;
}
