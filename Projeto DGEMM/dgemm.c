// compilando com: gcc -march=native -mavx -mfma -fopenmp -o dgemm.exe dgemm.c
// Windows 11

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dgemm.h"

#define n           1024
#define times       1
#define algorithm   0

/*
algorithm:
 1: DGEMM_1
 2: DGEMM_AVX
 3: DGEMM_AVX_UNROLL
 4: DGEMM_BLOCK_1
 5: DGEMM_AVX_UNROLL_BLOCK_2
 6: DGEMM_AVX_UNROLL_BLOCK_2_PARALLEL
 <1 || >6: ALL
*/

int main (void) {
    int z;
    clock_t start, end;
    double cpu_time_used, aux;

    double *A = criar_matriz (n);
    double *B = criar_matriz (n);
    double *C = criar_matriz (n);

    printf ("\nDGEMM %i x %i", n, n);

    switch (algorithm) {
        case 1:
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
        break;

        case 2:
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
        break;

        case 3:
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
        break;

        case 4:
            printf ("\n\nExecutando DGEMM_BLOCK_1 (%ix)", times);
            printf ("\n");
            aux = 0;

            for (z = 0; z < times; z++) {
                start = clock();
                dgemm_4 (n, A, B, C);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                aux += cpu_time_used;    
                printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
            }
        break;
            
        case 5:
            printf ("\n\nExecutando DGEMM_AVX_UNROLL_BLOCK_2 (%ix)", times);
            printf ("\n");
            aux = 0;

            for (z = 0; z < times; z++) {
                start = clock();
                dgemm_5 (n, A, B, C);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                aux += cpu_time_used;    
                printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
            }
        break;

        case 6:
            printf ("\n\nExecutando DGEMM_AVX_UNROLL_BLOCK_2_PARALLEL (%ix)", times);
            printf ("\n");
            aux = 0;

            for (z = 0; z < times; z++) {
                start = clock();
                dgemm_6 (n, A, B, C);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                aux += cpu_time_used;    
                printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
            }
        break;

        default:
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

            printf ("\nMedia DGEMM_1: %f sec", aux/times);

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

            printf ("\nMedia DGEMM_AVX: %f sec", aux/times);

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

            printf ("\nMedia DGEMM_AVX_UNROLL: %f sec", aux/times);

            printf ("\n\nExecutando DGEMM_AVX_UNROLL_BLOCK_1 (%ix)", times);
            printf ("\n");
            aux = 0;

            for (z = 0; z < times; z++) {
                start = clock();
                dgemm_4 (n, A, B, C);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                aux += cpu_time_used;    
                printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
            }

            printf ("\nMedia DGEMM_AVX_UNROLL_BLOCK_1: %f sec", aux/times);

            printf ("\n\nExecutando DGEMM_AVX_UNROLL_BLOCK_2 (%ix)", times);
            printf ("\n");
            aux = 0;

            for (z = 0; z < times; z++) {
                start = clock();
                dgemm_5 (n, A, B, C);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                aux += cpu_time_used;    
                printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
            }

            printf ("\nMedia DGEMM_AVX_UNROLL_BLOCK_2: %f sec", aux/times);

            printf ("\n\nExecutando DGEMM_AVX_UNROLL_BLOCK_2_PARALLEL (%ix)", times);
            printf ("\n");
            aux = 0;

            for (z = 0; z < times; z++) {
                start = clock();
                dgemm_6 (n, A, B, C);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                aux += cpu_time_used;    
                printf ("\nCPU time %i: %f sec", z + 1, cpu_time_used);
            }

            printf ("\nMedia DGEMM_AVX_UNROLL_BLOCK_2_PARALLEL: %f sec", aux/times);

            aux = -1;
        break;

    }

    if (aux > 0)
        printf ("\nMedia: %f sec", aux/times);
    printf ("\n");

    free_matrizes (A, B, C);

    return 0;
}