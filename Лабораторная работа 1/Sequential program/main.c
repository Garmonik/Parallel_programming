#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double t, double x){
    return x*t;
}

double fi(double x){
    return x*x*x / 12;
}

double ksi(double t){
    return t*t*t / 12;
}

void rectangle_solver(double *u, int x_size, double x_step, int t_size, double t_step, FILE *output_file) {
    int m, k;
    double c1 = t_step / (2 * x_step);
    double c2 = x_step / (2 * t_step);
    double *u_new = malloc(x_size * sizeof(double));

    for (k = 0; k < t_size-1; k++) {
        for (m = 1; m < x_size-1; m++) {
            u_new[m] = u[m] + c1*(u[m-1]-u[m+1]) + c2*(u[m+1]-2*u[m]+u[m-1]);
        }

        // boundary conditions
        u_new[0] = ksi(t_step * k);
        u_new[x_size-1] = fi(x_step * (x_size-1));

        for (m = 0; m < x_size; m++) {
            u[m] = u_new[m];
        }

        // write result to file
        for (m = 0; m < x_size-1; m++) {
            fprintf(output_file, "%.6f,", u[m]);
        }
        fprintf(output_file, "%.6f\n", u[x_size-1]);
    }

    free(u_new);
}

void initial_conditions(double *u, int x_size, double x_step) {
    int m;
    for (m = 0; m < x_size; m++) {
        u[m] = func(0, m * x_step);
    }
}

int main(){
    double t_max = 50;
    double x_max = 60;
    double t_step = 0.01;
    double x_step = 0.01;

    int x_size = (int)(x_max / x_step) + 1;
    int t_size = (int)(t_max / t_step) + 1;

    double *u = malloc(x_size * sizeof(double));
    initial_conditions(u, x_size, x_step);

    FILE *output_file = fopen("output.csv", "w");
    rectangle_solver(u, x_size, x_step, t_size, t_step, output_file);
    fclose(output_file);

    free(u);

    return 0;
}

