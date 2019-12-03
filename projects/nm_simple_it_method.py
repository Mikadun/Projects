import numpy as np

def simple_iteration(A, f):
    ls = np.linalg.eig(A)[0]
    alpha, beta = min(ls), max(ls)
    koef = 2.0 / (alpha + beta)

    n = len(A)
    x = np.array([0] * n)

    for i in range(1000):
        x = x - (x * A - f) * koef

    return x
        
A = np.matrix([
    [10.9, 1.2, 2.1, 0.9],
    [1.2, 11.2, 1.5, 2.5],
    [2.1, 1.5, 9.8, 1.3],
    [0.9, 2.5, 1.3, 12.1]
])

b = np.array([-7.0, 5.3, 10.3, 24.6])

x = simple_iteration(A, b)
print(np.around(x, 2))