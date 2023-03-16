#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
    const int N = 100000000; // количество точек
    int count = 0; // количество точек, попавших в круг
    double R = 1.0; // радиус круга
    double x, y; // координаты точки
    double pi; // приближенное значение числа pi
    int i, rank, size;

    MPI_Init(&argc, &argv); // инициализация MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // получение номера процесса
    MPI_Comm_size(MPI_COMM_WORLD, &size); // получение количества процессов

    srand(rank); // инициализация генератора случайных чисел для каждого процесса

    int local_count = 0; // количество точек, попавших в круг, для каждого процесса
    for (i = rank; i < N; i += size) {
        x = (double)rand() / RAND_MAX * 2 * R - R; // генерируем случайную координату x
        y = (double)rand() / RAND_MAX * 2 * R - R; // генерируем случайную координату y
        if (sqrt(x*x + y*y) <= R) { // проверяем, попадает ли точка внутрь круга
            local_count++;
        }
    }

    MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // суммируем результаты каждого процесса

    if (rank == 0) {
        pi = 4.0 * count / N / size; // вычисляем приближенное значение числа pi
        printf("Pi is approximately %.16f\n", pi*2);
    }

    MPI_Finalize(); // завершение MPI

    return 0;
}
