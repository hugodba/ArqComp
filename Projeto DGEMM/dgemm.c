#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dgemm.h"

int main (void) {

    printf ("\ncomeco\n");
    int n = 2048;
    int aux1, aux2, aux3, aux4;
    
    double *A = malloc (n * n * sizeof (double));
    double *B = malloc (n * n * sizeof (double));
    double *C = malloc (n * n * sizeof (double));

    clock_t start, end;
    double cpu_time_used;

/*
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            A[i+j*n] = 2.56;
            B[i+j*n] = 2.56;
        }
*/
    start = clock();
    dgemm_1 (n, A, B, C);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf ("\nCPU time: %f\n", cpu_time_used);
    
    free (A);
    free (B);
    free (C);
    return 0;
}
