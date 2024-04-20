// compilando com: gcc -march=native -mavx -mfma -fopenmp -o dgemm.exe dgemm.c
// Windows 11

#include "dgemm.h"

#define n           2048
#define times       10
#define algorithm   6

/*
algorithm:
 1: DGEMM_1
 2: DGEMM_AVX
 3: DGEMM_AVX_UNROLL
 4: DGEMM_BLOCK_1
 5: DGEMM_AVX_UNROLL_BLOCK_2
 6: DGEMM_AVX_UNROLL_BLOCK_2_PARALLEL
 <1 || >6: all
*/

int main (void) {
    double media;

    double *A = criar_matriz (n);
    double *B = criar_matriz (n);
    double *C = criar_matriz (n);

    printf ("\nDGEMM %i x %i", n, n);

    if (algorithm < 1 || algorithm > 6) {
        for (int i = 1; i < 7; i++) {
                media = executar_dgemm (n, times, i, A, B, C);
                printf ("\nMedia: %f sec", media);
        }
    }

    else {
        media = executar_dgemm (n, times, algorithm, A, B, C);
        printf ("\nMedia: %f sec", media);
    }

    free (A);
    free (B);
    free (C);

    return 0;
}