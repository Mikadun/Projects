import numpy as np
np.set_printoptions(precision=2, suppress=True)

def Richard(A, f, k):
    n = len(f)
    ls = np.linalg.eig(A)[0]
    a, b = min(ls), max(ls)
    x = np.array([0.0] * n)

    for i in range(k):
        t = 2 / ((a + b) + (b - a) * np.cos((2*i - 1) * np.pi / (2 * k)))
        x += t * (f - np.array(x * A)[0])

    return x


A = np.matrix([
    [10.9, 1.2, 2.1, 0.9],
    [1.2, 11.2, 1.5, 2.5],
    [2.1, 1.5, 9.8, 1.3],
    [0.9, 2.5, 1.3, 12.1]
])

b = np.array([-7.0, 5.3, 10.3, 24.6])

print(Richard(A, b, 16))