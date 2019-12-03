import numpy as np
from math import sqrt

def MSR(A):
    n = len(A)
    W = np.matrix([[0.0] * n for _ in range(n)])

    W[0, 0] = sqrt(A[0][0])

    for j in range(1, n):
        W[0, j] = A[0][j] / W[0, 0]

    for i in range(1, n):
        W[i, i] = sqrt(A[i][i] - sum([W[k, i] ** 2 for k in range(i)]))
        for j in range(i + 1, n):
            if j != i:
                W[i, j] = (A[i][j] - sum([W[k, i] * W[k, j] for k in range(i)])) / W[i, i]
    
    return W

def solve(A, b):
    W = MSR(A)
    n = len(A)
    y = [0] * n

    y[0] = b[0] / W[0, 0]
    for i in range(n):
        y[i] = (b[i] - sum([W[k, i] * y[k] for k in range(i)])) / W[i, i]
    
    x = [0] * n
    x[n - 1] = y[n - 1] / W[n - 1, n - 1]
    
    for i in range(n - 2, -1, -1):
        x[i] = (y[i] - sum([W[i, k] * x[k] for k in range(i + 1, n)])) / W[i, i]

    return x

A = [
    [2.12, 0.42, 1.34, 0.88],
    [0.42, 3.95, 1.87, 0.43],
    [1.34, 1.87, 2.98, 0.46],
    [0.88, 0.43, 0.46, 4.44]
]

b = [11.172, 0.115, 9.009, 9.349]

x = list(map(lambda x: round(x, 1), solve(A, b)))
print(x)
