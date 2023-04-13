#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double t_max = 50;
double x_max = 60;
double t_step = 0.01;
double x_step = 0.01;

double func(double t, double x){
    return x*t;
}

double fi(double x){
    return x*x*x / 12;
}

double ksi(double t){
    return t*t*t / 12;
}

int main(int argc, char *argv[]) {
    int size, rank;
    double tau = t_step;
    double h = x_step;
    double t, x;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int K = (int)(t_max / tau);
    int M = (int)(x_max / h);

    double **u = (double**)malloc((K+1) * sizeof(double*)); // выделение памяти под двумерный массив
    for (int k = 0; k <= K; k++) {
        u[k] = (double*)malloc((M+1) * sizeof(double));
    }

    // инициализация начальных условий
    for (int m = 0; m <= M; m++) {
        u[0][m] = fi(m*h);
    }
    for (int k = 0; k <= K; k++) {
        u[k][0] = ksi(k*tau);
    }

    // вычисление сеточной функции
    for (int k = 0; k < K; k++) {
        for (int m = 1; m <= M; m++) {
            t = k * tau;
            x = m * h;
            double f = func(t + tau/2, x + h/2);
            double a = u[k][m-1] - u[k][m];
            double b = u[k][m] - u[k][m-1];
            double c = u[k+1][m-1] - u[k][m-1];
            u[k+1][m] = u[k][m] - (tau/h) * (a + b) + 0.5 * tau * f + 0.5 * tau * (tau/h) * c;
        }
    }

    // output results
    if(rank == 0){
        FILE *fp;
        fp = fopen("output.csv", "w+");
        for(int k = 0; k <= K; k++){
            for(int m = 0; m <= M; m++){
                fprintf(fp, "%f,%f,%f\n", m*h, k*tau, u[k][m]);
            }
        }
        fclose(fp);
    }

    // освобождение памяти
    for (int k = 0; k <= K; k++) {
        free(u[k]);
    }
    free(u);

    MPI_Finalize();

    return 0;
}

