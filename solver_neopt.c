/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");

	double *result = malloc (N * N * sizeof(double));
	double *result1 = malloc (N * N * sizeof(double));
	double *result2 = malloc (N * N * sizeof(double));

	if (result == NULL || result1 == NULL || result2 == NULL) {
		perror("Malloc failed!");
		return NULL;
	} 

	int i, j, k;

	/* Calculare A^T*B */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result1[i * N + j] = 0.0;
    		
			for (k = 0; k < N; k++) {
				result1[i * N + j] += A[i + k * N] * B[k * N + j];
      			}
   		}
	}

	/* Calculare B^T*A */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result2[i * N + j] = 0.0;
    		
			for (k = 0; k < N; k++) {
				result2[i * N + j] += B[i + k * N] * A[k * N + j];
      			}
   		}
	}

	/* Calculare A^T*B + B^T*A */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result1[i * N + j] += result2[i * N + j];		
		}
	}

	/* Umplere cu 0 sub diagonala principala */
	for (i = 1; i < N; i++) {
		for (j = 0; j < i; j++) {
			result1[i * N + j] = 0;
		}
	}

	/* Calcularea rezultatului final */
	for (i = 0; i < N; i++) {
   		for (j = 0; j < N; j++) {
      			result[i * N + j] = 0.0;

			for (k = 0; k < N; k++) {
				result[i * N + j] += result1[i * N + k] * result1[k * N + j];
      			}
   		}
	}

	free(result1);
	free(result2);

	return result;
}
