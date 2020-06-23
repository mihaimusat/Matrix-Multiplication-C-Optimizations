/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"
#include "cblas.h"

// B * At  + A^2 * B

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {

	int i, j;

	// salveaza valoarea lui B pentru cea de-a doua operatie
	double *B1 = (double*)calloc(N * N, sizeof(double));
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			B1[i * N + j] = B[i * N + j];
		}
	}
	
	// acum fac B = B * At
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, B, N);
	
	// acum fac B1 = A * B1
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, B1, N);

	// salveaza valoarea lui B1 in B2
	double *B2 = (double*)calloc(N * N, sizeof(double));
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			B2[i * N + j] = B1[i * N + j];
		}
	}

	// acum fac B2 = A * B2
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, B2, N);
	
	// calculeaza C = B + B2
	double *C = (double*)calloc(N * N, sizeof(double));
    	for(i = 0; i < N; i++) {  
        	for(j = 0; j < N; j++) { 
            		C[i * N + j] = B[i * N + j] + B2[i * N + j];
		}
	}
	
	free(B1);
	free(B2);

	return C;
}
