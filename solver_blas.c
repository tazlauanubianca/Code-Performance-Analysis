/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include "cblas.h"

double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	
	double *result = calloc(N * N, sizeof(double));
	double *result1 = calloc(N * N, sizeof(double));
   	double *result2 = calloc(N * N, sizeof(double));
	double one = 1.0, zero = 0.0;
	int i, j;

	/* Calculare A^T*B si B^T*A */
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N,N, one, A, N, B, N, zero, result1, N);
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N,N, one, B, N, A, N, zero, result2, N);
	
	/* Calcularea sumei celor doua rezultate partiale */
	for (i = 0; i < N; i++)
		for (j = i; j < N; j++)
			result[i * N + j] = result1[i * N + j] + result2[i * N + j];
	
	/* Calcularea rezultatului final */
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, one, result, N, result, N, zero, result, N);

	return result;
}
