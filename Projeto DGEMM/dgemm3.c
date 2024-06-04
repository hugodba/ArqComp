#include <stdio.h>
#include <windows.h>
#include <x86intrin.h>

#define N 1000

void mult(double* A, double* B, double* C) {
    size_t i, j, k;
    for (i = 0; i < N; i += 4) {
        for (j = 0; j < N; j++) {
            __m256d c0 = _mm256_load_pd(C + i + j * N); /* c0 = C[i][j] */
            for (k = 0; k < N; k++) {
                c0 = _mm256_add_pd(c0, /* c0 += A[i][k] * B[k][j] */
                    _mm256_mul_pd(_mm256_load_pd(A + i + k * N),
                    _mm256_broadcast_sd(B + k + j * N)));
            }
            _mm256_store_pd(C + i + j * N, c0); /* C[i][j] = c0 */
        }
    }
}


void create_matrix(double *A){
  srand(time(NULL));
    int i, j;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
        A[i*N+j] = (double)(rand() % 100) + 0.01 * (rand() % 100);
        if (rand() % 2 == 0) A[i*N+j] *= 1.0;
    }
  }
}

int main(){
    int i,j;
    double *A=NULL,*B=NULL,*C=NULL;

    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end; 
    double elapsed_time;
    QueryPerformanceFrequency(&frequency);

    A = (double *)malloc(sizeof(double)*N*N);
    B = (double *)malloc(sizeof(double)*N*N);
    C = (double *)malloc(sizeof(double)*N*N);

    create_matrix(A);
    create_matrix(B);
    create_matrix(C);

    QueryPerformanceCounter(&start);
    mult(A, B, C);
    QueryPerformanceCounter(&end);

    elapsed_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Tempo decorrido: %f segundos\n", elapsed_time);

    return 0;
}

//gcc -mavx -o dgemm3 dgemm3.c
