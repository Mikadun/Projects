import numpy as np
np.set_printoptions(precision=2, suppress=True)
 
def QR(A):
    m, n = A.shape
    Q = np.eye(m)
    for i in range(n - (m == n)):
        P = np.eye(m)
        P[i:, i:] = step(A[i:, i])
        Q = np.dot(Q, P)
        A = np.dot(P, A)
    return np.matrix(Q), np.matrix(A)
 
def step(a):
    v = a / (a[0] + np.copysign(np.linalg.norm(a), a[0]))
    v[0] = 1
    P = np.eye(a.shape[0])
    P -= (2 / np.dot(v, v)) * np.dot(v[:, None], v[None, :])
    return P

def solve(A, b):
    Q, R = QR(A)
    n = len(A)
    y = Q.T * b[np.newaxis].T
    x = [0] * n
    x[n - 1] = y[n - 1] / R[n - 1, n - 1]
    for i in range(n - 1, -1, -1):
        x[i] = (y[i] - sum([R[i, k] * x[k] for k in range(i + 1, n)])).item() / R[i, i]

    return np.array(x)

A = np.array((
    (2, 5, 3),
    (4, 2, 3),
    (7, 8, 5)
), dtype = float)

b = np.array([4, 2, 3])

print(solve(A, b))
print(np.linalg.solve(A, b))
