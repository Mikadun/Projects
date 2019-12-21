import numpy as np
np.set_printoptions(precision=2, suppress=True)

def relax_method(A, f):
    n = len(f)
    xp = x = np.array([0.0] * n)
    w = 1.2

    for k in range(100):
        for i in range(n):
            S1 = sum((A[i, j] * x[j] for j in range(i)))
            S2 = sum((A[i, j] * xp[j] for j in range(i + 1, n)))
            x[i] = (w * (f[i] - S1 - S2) + (1 - w) * A[i, i] * xp[i]) / A[i, i]

        xp = x
    
    return x

A = np.matrix([
    [10.9, 1.2, 2.1, 0.9],
    [1.2, 11.2, 1.5, 2.5],
    [2.1, 1.5, 9.8, 1.3],
    [0.9, 2.5, 1.3, 12.1]
])

b = np.array([-7.0, 5.3, 10.3, 24.6])

A2 = np.matrix([
    [3.82, 1.02, 0.75, 0.81],
    [1.05, 4.53, 0.98, 1.53],
    [0.73, 0.85, 4.71, 0.81],
    [0.88, 0.81, 1.28, 3.50]
])

b2 = np.array([15.655, 22.705, 23.480, 16.110])

print(relax_method(A2, b2))
print(np.linalg.solve(A2, b2))
