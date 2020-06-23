/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

// B * At  + A^2 * B

/*
 * Add your unoptimized implementation here
 */

// functie care calculeaza transpusa unei matrici
double *transpose_matrix(int N, double *A) {

	int i, j;
	double *tr = (double*)malloc(N * N * sizeof(double));

	if(tr == NULL)
		return NULL;
	
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			tr[j * N + i] = A[i * N + j];

	return tr;
}

// functie care calculeaza adunarea intre doua matrici
double *add_matrix(int N, double *A, double *B) {

	int i, j;	
	double *add = (double*)malloc(N * N * sizeof(double));

	if(add == NULL)
		return NULL;

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			add[i * N + j] = A[i * N + j] + B[i * N + j];
		}
	}

	return add;
}

double* my_solver(int N, double *A, double* B) {

	int i, j, k;

	// calculeaza transpusa matricei A
	double *A_t = transpose_matrix(N, A);
	
	// retine primul termen ca fiind B * At
	double *first_term = (double*)malloc(N * N * sizeof(double));
	if(first_term == NULL)
		return NULL;

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = j; k < N; k++)
				first_term[i * N + j] += B[i * N + k] * A_t[k * N + j];
		}
	}
	
	// acum fac A2 = A * A
	double *A2 = (double*)malloc(N * N * sizeof(double));
	if(A2 == NULL)
		return NULL;

	for(i = 0; i < N; i++) {
		for(j = i; j < N; j++) {
			for(k = i; k <= j; k++)
				A2[i * N + j] += A[i * N + k] * A[k * N + j];
		}
	}

	// retine al doilea termen ca fiind A2 * B
	double *second_term = (double*)malloc(N * N * sizeof(double));
	if(second_term == NULL)
		return NULL;
		
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = i; k < N; k++)
				second_term[i * N + j] += A2[i * N + k] * B[k * N + j];
		}
	}

	// rezultatul va fiind adunarea celor doi termeni
	double *result = add_matrix(N, first_term, second_term);

	free(A_t);
	free(A2);
	
	return result;
}
