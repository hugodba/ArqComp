#include <stdio.h>
#include <windows.h>


#define N 2000


void mult (double* A, double* B, double* C){
  int i, j, k;
  for (i = 0; i < N; ++i){
    for (j = 0; j < N; ++j){
      double cij = C[i+j*N]; /* cij = C[i][j] */
      for(k = 0; k < N; k++ ){
        cij += A[i+k*N] * B[k+j*N]; /* cij += A[i][k]*B[k][j] */
        C[i+j*N] = cij; /* C[i][j] = cij */
      }
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