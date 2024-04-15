#include <x86intrin.h>
#include <omp.h>

#define UNROLL    4
#define BLOCKSIZE 32
#define THREADS   8

double rand_double (double, double);
double rand_double (double min, double max) {
    double random = ((double) rand ()) / RAND_MAX;
    double range = (max - min) * random;
    double number = min + range;
    return number;
}

void rand_matrix (int, double *, int, int);
void rand_matrix (int n, double *A, int min, int max) {

  srand (time(NULL));

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) 
      A[i+j*n] = rand_double (min, max);
}

double *criar_matriz (int);
double *criar_matriz (int n) {
  double *matriz = malloc (n * n * sizeof (double));
  rand_matrix (n, matriz, 0, 1000);
  return matriz;
}

void free_matrizes (double *, double *, double *);
void free_matrizes (double *A, double *B, double *C) {
  free (A); free (B); free (C);
}

void dgemm_1 (int, double *, double *, double *);
void dgemm_1 (int n, double *A, double *B, double *C) {
    double cij;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            cij = C[i+j*n]; /* cij = C[i][j] */
            for( int k = 0; k < n; k++ )
                cij += A[i+k*n] * B[k+j*n]; /* cij += A[i][k]*B[k][j] */
            C[i+j*n] = cij; /* C[i][j] = cij */
        }
}

void dgemm_2 (size_t, double *, double *, double *);
void dgemm_2 (size_t n, double *A, double *B, double *C) {
    for ( size_t i = 0; i < n; i+=4 )
        for ( size_t j = 0; j < n; j++ ) {
            __m256d c0 = _mm256_load_pd(C+i+j*n); /* c0 = C[i][j] */
            for( size_t k = 0; k < n; k++ ) 
                c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
                     _mm256_mul_pd(_mm256_load_pd(A+i+k*n),
                     _mm256_broadcast_sd(B+k+j*n)));
            _mm256_store_pd(C+i+j*n, c0); /* C[i][j] = c0 */
            
        }
}

void dgemm_3 (int, double *, double *, double *);
void dgemm_3 (int n, double *A, double *B, double *C) {
  for (int i = 0; i < n; i+=UNROLL*8)
    for (int j = 0; j < n; ++j){
      __m256d c[UNROLL];
      for (int r=0;r<UNROLL;r++){
        c[r] = _mm256_load_pd(C+i+r*8+j*n); //[ UNROLL];
      }

      for( int k = 0; k < n; k++ ) {
        __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B+j*n+k));
        for (int r=0;r<UNROLL;r++)
          c[r] = _mm256_fmadd_pd(_mm256_load_pd(A+n*k+r*8+i), bb, c[r]);
      }

      for (int r=0;r<UNROLL;r++)
        _mm256_store_pd(C+i+r*8+j*n, c[r]);
    }
}

void do_block_1 (int, int, int, int, double *, double *, double *);
void do_block_1 (int n, int si, int sj, int sk, double *A, double *B, double *C) {
  for (int i = si; i < si+BLOCKSIZE; ++i)
    for (int j = sj; j < sj+BLOCKSIZE; ++j) {
      double cij = C[i+j*n];/* cij = C[i][j] */
      for( int k = sk; k < sk+BLOCKSIZE; k++ )
        cij += A[i+k*n] * B[k+j*n];/* cij+=A[i][k]*B[k][j] */
      C[i+j*n] = cij;/* C[i][j] = cij */
    }
}

void do_block_2 (int, int, int, int, double *, double *, double *);
void do_block_2 (int n, int si, int sj, int sk, double *A, double *B, double *C) {
  for ( int i = si; i < si+BLOCKSIZE; i+=UNROLL*8 )
    for ( int j = sj; j < sj+BLOCKSIZE; j++ ) {
      __m256d c[UNROLL];
      for (int r=0;r<UNROLL;r++)
        c[r] = _mm256_load_pd(C+i+r*8+j*n); //[ UNROLL];

      for( int k = sk; k < sk+BLOCKSIZE; k++ ) {
        __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B+j*n+k));
        for (int r=0;r<UNROLL;r++)
          c[r] = _mm256_fmadd_pd(_mm256_load_pd(A+n*k+r*8+i), bb, c[r]);
      }

      for (int r=0;r<UNROLL;r++)
        _mm256_store_pd(C+i+r*8+j*n, c[r]);
    }
}

void dgemm_4 (int, double *, double *, double *);
void dgemm_4 (int n, double* A, double* B, double* C) {
  for ( int sj = 0; sj < n; sj += BLOCKSIZE )
    for ( int si = 0; si < n; si += BLOCKSIZE )
      for ( int sk = 0; sk < n; sk += BLOCKSIZE )
        do_block_1 (n, si, sj, sk, A, B, C);
}

void dgemm_5 (int, double *, double *, double *);
void dgemm_5 (int n, double* A, double* B, double* C) {
  for ( int sj = 0; sj < n; sj += BLOCKSIZE )
    for ( int si = 0; si < n; si += BLOCKSIZE )
      for ( int sk = 0; sk < n; sk += BLOCKSIZE )
        do_block_2 (n, si, sj, sk, A, B, C);
}

void dgemm_6 (int, double *, double *, double *);
void dgemm_6 (int n, double* A, double* B, double* C) {
  omp_set_num_threads(THREADS);
#pragma omp parallel for
  for ( int sj = 0; sj < n; sj += BLOCKSIZE )
    for ( int si = 0; si < n; si += BLOCKSIZE )
      for ( int sk = 0; sk < n; sk += BLOCKSIZE )
        do_block_2 (n, si, sj, sk, A, B, C);
}