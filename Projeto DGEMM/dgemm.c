#include <stdio.h>
#include <time.h>
#include "dgemm.h"

int main (void) {

    printf ("\ncomeco\n");
    int n = 1024;
    
    double A [n*n];
    double B [n*n];
    double C [n*n];

    clock_t start, end;
    double cpu_time_used;

    printf ("\ndebug1");
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

    return 0;
}