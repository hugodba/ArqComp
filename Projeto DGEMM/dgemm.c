// compilando com: gcc -Wall -mavx512f -mavx512cd -o dgemm.exe dgemm.c

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dgemm.h"

#define n       1024
#define times   3

int main (void) {
    
    double *A = malloc (n * n * sizeof (double));
    double *B = malloc (n * n * sizeof (double));
    double *C = malloc (n * n * sizeof (double));
    int z;
    clock_t start, end;
    double cpu_time_used, aux;

    printf ("\nDGEMM %i x %i", n, n);
    printf ("\n\nConstruindo matriz");

    srand (time(NULL));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
        {
            A[i+j*n] = rand_double (0, 1000);
            B[i+j*n] = rand_double (0, 1000);
        }
    }


    printf ("\n\nExecutando DGEMM_1 (%ix)", times);
    printf ("\n");
    aux = 0;

    for (z = 0; z < times; z++) {
        start = clock();
        dgemm_1 (n, A, B, C);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        aux += cpu_time_used;
        printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
    }

    printf ("\nMedia: %f sec", aux/times);

    printf ("\n\nExecutando DGEMM_AVX (%ix)", times);
    printf ("\n");
    aux = 0;

    for (z = 0; z < times; z++) {
        start = clock();
        dgemm_2 (n, A, B, C);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        aux += cpu_time_used;
        printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
    }

    printf ("\nMedia: %f sec", aux/times);

    printf ("\n\nExecutando DGEMM_AVX_UNROLL (%ix)", times);
    printf ("\n");
    aux = 0;

    for (z = 0; z < times; z++) {
        start = clock();
        dgemm_3 (n, A, B, C);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        aux += cpu_time_used;    
        printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
    }

    printf ("\nMedia: %f sec", aux/times);

    free (A);
    free (B);
    free (C);
    return 0;
}