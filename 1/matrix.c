#include <stdio.h>
#include <stdlib.h>

double* create_matrix(int rows, int cols);
void free_matrix(double* matrix);
void transpose_matrix(double* result, double* matrix, int rows, int cols);
void add_matrices(double* result, double* matrix1, double* matrix2, int rows, int cols);
void multiply_matrices(double* result, double* matrix1, double* matrix2, int rows1, int cols1, int cols2);
void dump_matrix(double* matrix, int rows, int cols);

int main() {
    int rows = 2, cols = 3;
    double* matrix1 = create_matrix(rows, cols);
    double* matrix2 = create_matrix(rows, cols);
    double* result = create_matrix(rows, cols);

    matrix1[0] = 1; matrix1[1] = 2; matrix1[2] = 3;
    matrix1[3] = 4; matrix1[4] = 5; matrix1[5] = 6;

    matrix2[0] = 6; matrix2[1] = 5; matrix2[2] = 4;
    matrix2[3] = 3; matrix2[4] = 2; matrix2[5] = 1;

    printf("Matrix 1:\n");
    dump_matrix(matrix1, rows, cols);
    
    printf("Matrix 2:\n");
    dump_matrix(matrix2, rows, cols);

    add_matrices(result, matrix1, matrix2, rows, cols);
    printf("相加:\n");
    dump_matrix(result, rows, cols);

    double* transpose_result = create_matrix(cols, rows);
    transpose_matrix(transpose_result, matrix1, rows, cols);
    printf("轉置Matrix 1:\n");
    dump_matrix(transpose_result, cols, rows);

    int rows1 = 2, cols1 = 3, cols2 = 2;
    double* matrix3 = create_matrix(cols1, cols2);
    matrix3[0] = 1; matrix3[1] = 2;
    matrix3[2] = 3; matrix3[3] = 4;
    matrix3[4] = 5; matrix3[5] = 6;
    
    double* multiply_result = create_matrix(rows1, cols2);
    multiply_matrices(multiply_result, matrix1, matrix3, rows1, cols1, cols2);
    printf("相乘:\n");
    dump_matrix(multiply_result, rows1, cols2);

    return 0;
}

double* create_matrix(int rows, int cols) {
    return (double*)malloc(rows * cols * sizeof(double));
}

void transpose_matrix(double* result, double* matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
}

void add_matrices(double* result, double* matrix1, double* matrix2, int rows, int cols) {
    for (int i = 0; i < rows * cols; ++i) {
        result[i] = matrix1[i] + matrix2[i];
    }
}

void multiply_matrices(double* result, double* matrix1, double* matrix2, int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            result[i * cols2 + j] = 0;
            for (int k = 0; k < cols1; ++k) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

void dump_matrix(double* matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%lf ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}