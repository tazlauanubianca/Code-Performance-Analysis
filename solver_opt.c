/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SM 40

double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	double *result = calloc (N * N, sizeof(double));
	double *result1 = calloc (N * N, sizeof(double));

	if (result == NULL || result1 == NULL) {
		perror("Malloc failed!");
		return NULL;
	}

	int bi, bj, bk, i, j, k;

	/* Calculare matrice inferioara A^T*B + B^T*A */
	for(bi = 0; bi < N; bi += SM) {
		for(bk = 0; bk < N; bk += SM) {
			for(bj = 0; bj <= bi; bj += SM) { 
    			for (i = 0; i < SM; i++) {
					for (k = 0; k < SM; k++) {
						register double *ptr_res_tr = result1 + i + bi + bj * N;
						register double *ptr_a = A + i + k * N + bk * N + bi;
						register double *ptr_b = B + k * N + bk * N + bj;

						for (j = 0; j < SM; j++) {
							if (j + bj <= i + bi)
								*ptr_res_tr += (*ptr_a) * (*ptr_b);

							ptr_b++;
							ptr_res_tr += N;			
						}
					}
				}
			}
		}
	}
	
	/* Calculare matrice superioara A^T*B + B^T*A */
	for(bi = 0; bi < N; bi += SM) {
    		for(bk = 0; bk < N; bk += SM) {
			for(bj = bi; bj < N; bj += SM) {
				for (i = 0; i < SM; i++) {
					for (k = 0; k < SM; k++) {
						register double *ptr_res = result1 + i * N + bi * N + bj;
						register double *ptr_a = A + i + k * N + bk * N + bi;
						register double *ptr_b = B + k * N + bk * N + bj;

						for (j = 0; j < SM; j++) {
							if (j + bj >= i + bi)
								*ptr_res += (*ptr_a) * (*ptr_b);
						
							ptr_res++;
							ptr_b++;
						}
					}
				}
			}
		}
	}

	/* Calculare rezultat final. */
	for (i = 0; i < N; i++) {
		for (k = 0; k < N; k++) {
			register double *ptr_res = result + i * N + i;
			register double *ptr_b = result1 + k * N + i;
			register double var = result1[i * N + k];

			for (j = i; j < N; j++) {
				(*ptr_res) += var * (*ptr_b);
				ptr_res++;
				ptr_b++;
			}
		}
	}
	
	return result;
}
