import numpy as np
np.set_printoptions(precision=2, suppress=True)

def get_max(A):
    idx = (1, 0)
    for i in range(A.shape[0]):
        for j in range(i):
            if abs(A[idx]) < abs(A[i, j]):
                idx = (i, j)
    return idx

def rotation_method(A):

    for k in range(15):
        l, m = get_max(A)
        angle = np.arctan(2 * A[l, m] / (A[l, l] - A[m, m])) / 2
        T = np.eye(A.shape[0])
        T[l, l] = np.cos(angle)
        T[l, m] = -np.sin(angle)
        T[m, l] = np.sin(angle)
        T[m, m] = np.cos(angle)

        A = T.T * A * T

    return A

A = np.matrix([
    [-0.168700, 0.353699, 0.008540, 0.733624],
    [0.353699, 0.056519, 0.723182, -0.076440],
    [0.008540, 0.723182, 0.015938, 0.342333],
    [0.733624, -0.076440, 0.342333, -0.045744]
])

print(rotation_method(A))
print(np.linalg.eig(A)[0])