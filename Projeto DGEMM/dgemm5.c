#include <stdio.h>
#include <windows.h>
#include <x86intrin.h>

#define N 1024
#define UNROLL 4
#define BLOCKSIZE 32

void do_block (int si, int sj, int sk, double *A, double *B, double *C){
    for ( int i = si; i < si+BLOCKSIZE; i+=UNROLL*8 )
        for ( int j = sj; j < sj+BLOCKSIZE; j++) {
        __m256d c[UNROLL];
        for ( int r = 0; r < UNROLL; r++)
            c[r] = _mm256_load_pd(C+i+r*4+j*N);
        for (int k = sk; k < sk+BLOCKSIZE; k++ ){
            __m256d b = _mm256_broadcast_sd(B+k+j*N);
            for (int r = 0; r < UNROLL; r++)
                c[r] = _mm256_add_pd(c[r], _mm256_mul_pd(_mm256_load_pd(A+N*k+r*4+i), b));
        }
        for ( int r = 0; r < UNROLL; r++ )
            _mm256_store_pd(C+i+r*4+j*N, c[r]);
        }
} 

void mult (double* A, double* B, double* C){
    for(int sj = 0; sj < N; sj += BLOCKSIZE) 
        for(int si = 0; si < N; si += BLOCKSIZE) 
            for(int sk = 0; sk < N; sk += BLOCKSIZE) 
                do_block(si, sj, sk, A, B, C); 
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

//gcc -mavx -o dgemm dgemm.c