/*
August Ho und Benjamin von Behren

Compile: make matrix
Run: ./matrix
make matrix && ./matrix
*/

#include "base.h"

struct Matrix {
    int rows; // number of rows
    int cols; // number of columns
    double** data; // a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles
};
typedef struct Matrix Matrix;

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles
*/
Matrix* new_matrix(int n_rows, int n_cols) {
    // todo: implement
	double** n_data;
	n_data = xmalloc(sizeof(double*) * n_rows);

	require("valid row and column", n_rows > 0 && n_cols > 0);
	for (int i = 0; i < n_rows; i++) {
		n_data[i] = xmalloc(sizeof(double) * n_cols);
	}
	for (int j = 0; j < n_rows; j++) {	//number of rows
		for (int k = 0; k < n_cols; k++) {	//number of columns
			n_data[j][k] = 0;
		}
	}

	Matrix* a = xmalloc(sizeof(Matrix));
	a->rows = n_rows;
	a->cols = n_cols;
	a->data = n_data;
	//print_matrix(a);
    return a;
}

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] data an array of doubles, ordered row-wise
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles
*/
Matrix* copy_matrix(double* data, int n_rows, int n_cols) {

	// printf("%d\n", n_rows);
	// printf("%d\n", n_cols);
	// printf("%d\n", sizeof(data) / sizeof(*data));	//rows
	// printf("%d\n", sizeof(*data) / sizeof(**data));	//columns
	//require("valid row and column", sizeof(data)/sizeof(double) == n_rows * n_cols);

	require("valid row and column", n_rows > 0 && n_cols > 0);
    Matrix* matrix = new_matrix(n_rows, n_cols);
	//print_matrix(matrix);
	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_cols; j++) {
			//input row and column data from data
			matrix->data[i][j] = data[j+(i * n_cols)];
		}
	}
    return matrix;
}

/**
Print a matrix.
@param[in] m the matrix to print
*/
void print_matrix(Matrix* m) {
    // todo: implement
	require("valid matrix", m != NULL);
	for (int i = 0; i < m->rows; i++) {
  		for (int j = 0; j < m->cols; j++) {
			printf("  %6.2f", m->data[i][j]);
  		}
  		printf("\n");
	}
}

/**
Transpose a matrix.
@param[in] a the first operand
@return a new matrix whose elements are transposed
*/
Matrix* transpose_matrix(/*in*/ Matrix* a){
    // todo: implement
	Matrix* matrix = new_matrix(a->cols, a->rows);
	for (int i = 0; i < matrix->rows; i++) {
		for (int j = 0; j < matrix->cols; j++) {
			matrix->data[i][j] = a->data[j][i];
			ensure("new matrix data valid", matrix->data[i][j] == a->data[j][i]);
		}
	}
    return matrix;
}

/**
Multiplies two matrices.
@param[in] a the first operand
@param[in] b the second operand
@return a new matrix that is the result of the multiplication of a * b
*/
Matrix* mul_matrices(/*in*/ Matrix* a, /*in*/ Matrix* b) {
    // todo: implement
	//require("valid row and column", n_rows > 0 && n_cols > 0);
	Matrix* result = new_matrix(a->rows, b->cols);
	double sum = 0.0;
	require("matrix forms match", a->cols == b->rows && a->rows == b->cols)
	result->data[0][0] = a->data[0][0] * b->data[0][0] + a->data[0][1] * b->data[1][0];
	for (int i = 0; i < result->rows; i++) {
		for (int j = 0; j < result->cols; j++) {
			sum = 0.0;
			for (int k = 0; k < a->cols; k++) {
				sum += a->data[i][k] * b->data[k][j];
			}
			result->data[i][j] = sum;
		}
	}
	ensure("valid rows and colums", result->rows == a->rows && result->cols == b->cols);
	return result;
}

/**
Free a matrix.
@param[in] m the matrix to free
*/
void free_matrix(Matrix* m) {
    // todo: implement
	// only rows used since they are made out of arrays of columns
	for (int i = 0; i < m->rows; i++) {
  		free(m->data[i]);
	}
	free(m->data);
	free(m);
}

void matrix_test(void) {
    printf("Create empty matrix: \n");

    Matrix* m0 = new_matrix(7, 1);
    print_matrix(m0);

    printf("Copy matrix data from double[]\n");

    double a[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9 };
    Matrix* m1 = copy_matrix(a, 3, 3);
    printf("m1:\n");
    print_matrix(m1);



    double a2[] = {
        1, 2, 3, 3.5,
        4, 5, 6, 7};
    Matrix* m2 = copy_matrix(a2, 2, 4);
    printf("m2:\n");
    print_matrix(m2);



    printf("Transpose: m2\n");
    Matrix* m2t = transpose_matrix(m2);
    print_matrix(m2t);


    double a3[] = {
        1, 2,
        3, 4,
        5, 6,
        7, 8};
    Matrix* m3 = copy_matrix(a3, 4, 2);
    printf("m3:\n");
    print_matrix(m3);

    Matrix* m3t = transpose_matrix(m3);
    printf("m3t:\n");
    print_matrix(m3t);

	printf("Multiply m3 * m3t\n");
    Matrix* m4 = mul_matrices(m3, m3t);
    printf("m4:\n");
    print_matrix(m4);

    free_matrix(m0);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m2t);
    free_matrix(m3);
    free_matrix(m3t);
    free_matrix(m4);

}

int main(void) {
    report_memory_leaks(true);
    matrix_test();
    return 0;
}
