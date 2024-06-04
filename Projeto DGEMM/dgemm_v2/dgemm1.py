import random
import time

N = 1000

def mult(A, B, C):
    for i in range(N):
        for j in range(N):
            cij = C[i][j]
            for k in range(N):
                cij += A[i][k] * B[k][j]
            C[i][j] = cij

def create_matrix():
    matrix = [[random.uniform(0, 100) for _ in range(N)] for _ in range(N)]
    return matrix

def main():
    A = create_matrix()
    B = create_matrix()
    C = [[0.0 for _ in range(N)] for _ in range(N)]

    start = time.time()
    mult(A, B, C)
    end = time.time()

    elapsed_time = end - start

    print(f"Tempo decorrido: {elapsed_time:.6f} segundos")

if __name__ == "__main__":
    main()
