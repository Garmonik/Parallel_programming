#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1000 // размер матрицы

int main(int argc, char** argv) {
    int rank, size;
    int i, j;
    int* matrix;
    int* block;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int block_size = N / size; // размер блока матрицы

    // выделение памяти для матрицы и блока
    if (rank == 0) {
        matrix = (int*)malloc(N * N * sizeof(int));
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                matrix[i * N + j] = i * N + j;
            }
        }
    }
    block = (int*)malloc(block_size * N * sizeof(int));

    // разбиение матрицы на блоки и их распределение
    MPI_Scatter(matrix, block_size * N, MPI_INT, block, block_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // транспонирование блока
    int* transposed_block = (int*)malloc(block_size * N * sizeof(int));
    for (i = 0; i < block_size; i++) {
        for (j = 0; j < N; j++) {
            transposed_block[j * block_size + i] = block[i * N + j];
        }
    }

    // объединение транспонированных блоков
    MPI_Gather(transposed_block, block_size * N, MPI_INT, matrix, block_size * N, MPI_INT, 0, MPI_COMM_WORLD);

    // вывод результата
    if (rank == 0) {
        printf("Transposed matrix:\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%d ", matrix[i * N + j]);
            }
            printf("\n");
        }
        free(matrix);
    }
    free(block);
    free(transposed_block);

    MPI_Finalize();
    return 0;
}
