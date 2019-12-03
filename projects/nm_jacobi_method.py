import numpy as np

def jacobi_method(A, f):
    n = len(f)
    x_prev = x = np.array([0.0] * n)

    for k in range(100):
        for i in range(n):
            S = sum([A[i, j] * x_prev[j] if i != j else 0 for j in range(n)])
            x[i] = (f[i] - S) / A[i, i]

        x_prev = x
    
    return x

A = np.matrix([
    [10.9, 1.2, 2.1, 0.9],
    [1.2, 11.2, 1.5, 2.5],
    [2.1, 1.5, 9.8, 1.3],
    [0.9, 2.5, 1.3, 12.1]
])

b = np.array([-7.0, 5.3, 10.3, 24.6])

x = jacobi_method(A, b)

print(np.around(x, 2))
