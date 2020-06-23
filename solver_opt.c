/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

// B * At  + A^2 * B

/*
 * Add your optimized implementation here
 */

// functie care calculeaza transpusa unei matrici
double *transpose_matrix(int N, double *A) {

	register int i, j;
	register double *tr = (double*)malloc(N * N * sizeof(double));

	if(tr == NULL)
		return NULL;

	register double *aux;
	
	for(i = 0; i < N; i++) {
		aux = tr + i;
		for(j = 0; j < N; j++) {
			*aux = *A;
			A++;
			if(j < N - 1)
				aux = aux + N;
		}

	}

	return tr;
}

// functie care calculeaza adunarea intre doua matrici
void add_matrix(int N, double *A, double *B, double *add) {

	register int i, j;
	register double *pa;
	register double *pb;
	register double *aux;

	for(i = 0; i < N; i++) {
		pa = A + i * N;
    		pb = B + i * N;
		aux = add + i * N;
		for(j = 0; j < N; j++) {
			*aux = *pa + *pb;
			aux++;
			pa++;
			pb++;
		}
	}
}

double* my_solver(int N, double *A, double* B) {
	
	register int i, j, k;
	
	register double suma = 0;
	register double *pa;
	register double *pb;

	// calculeaza transpusa matricei A
	register double *A_t = transpose_matrix(N, A);

	// retine primul termen ca fiind B * At
	register double *first_term = (double*)calloc(N * N, sizeof(double));
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			pa = A_t + j + j * N;			
			pb = B + i * N + j;
			suma = 0;
			for(k = j; k < N; k++) {
				suma += *pb * *pa;
				pb++;
				pa += N;			
			}
			first_term[i * N + j] = suma;
		}
	}
	
	// acum fac A2 = A * A
	register double *A2 = (double*)calloc(N * N, sizeof(double));
	
	for(i = 0; i < N; i++) {
		for(j = i; j < N; j++) {
			pa = A + i * N + i;
			pb = A + j + i * N;
			suma = 0;
			for(k = i; k <= j; k++) {
				suma += *pa * *pb;
				pa++;
				pb += N;
			}
			A2[i * N + j] = suma;
		}
	}
	
	// retine al doilea termen ca fiind A2 * B
	register double *second_term = (double*)calloc(N * N, sizeof(double));
		
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			pa = A2 + i * N + i;
			pb = B + j + i * N;
			suma = 0;
			for(k = i; k < N; k++) {
				suma += *pa * *pb;
				pa++;
				pb += N;
			}
			second_term[i * N + j] = suma;
		}
	}

	// rezultatul va fiind adunarea celor doi termeni
	register double *result = (double*)calloc(N * N ,sizeof(double));
	add_matrix(N, first_term, second_term, result);

	free(A_t);
	free(A2);

	return result;
}
