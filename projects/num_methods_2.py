
import numpy as np
np.set_printoptions(precision=2)

A = np.array([
	[0.411, 0.421, -0.333, 0.313, -0.141, -0.381, 0.245],
	[0.241, 0.705, 0.139, -0.409, 0.321, 0.0625, 0.101],
	[0.123, -0.239, 0.502, 0.901, 0.243, 0.819, 0.321],
	[0.413, 0.309, 0.801, 0.865, 0.423, 0.118, 0.183],
	[0.241, -0.221, -0.243, 0.134, 1.274, 0.712, 0.423],
	[0.281, 0.525, 0.719, 0.118, -0.974, 0.808, 0.923],
	[0.246, -0.301, 0.231, 0.813, -0.702, 1.223, 1.105]
])

b = np.array([0.096, 1.252, 1.024, 1.023, 1.155, 1.937, 1.673])

x = np.array([0.18691, 0.60228, 0.52468, -0.10430, 0.35477, 0.65180, 1.1075])

n = len(b)

def LU():
	L = [[0 for i in range(n)] for j in range(n)]
	U = [[0 for k in range(n)] for l in range(n)]

	getU = lambda i, j: (A[i][j] - sum([L[i][k] * U[k][j] for k in range(i)]))
	getL = lambda i, j: (A[i][j] - sum([L[i][k] * U[k][j] for k in range(j)])) / U[j][j]

	for i in range(n):
		for j in range(i, n):
			U[i][j] = getU(i, j)

		for j in range(i, n):
			L[j][i] = getL(j, i)

	return (L, U) # np.matrix()

def solve():
	L, U = LU()
	y = []
	for i in range(n):
		y.append(b[i] - sum([L[i][k] * y[k] for k in range(i)]))

	x = [0] * n
	for i in range(n - 1, -1, -1):
		x[i] = (y[i] - sum([U[i][k] * x[k] for k in range(i + 1, n)])) / U[i][i]

	return x

print(solve())



