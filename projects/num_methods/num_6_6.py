import numpy as np
n = 11
eps = 0.0001
N = n - 1
h = 1 / n
x = [i * h for i in range(n)]
y = [i * h for i in range(n)]
f = lambda x, y: x + y ** 2
u = [[0 for i in range(n)] for j in range(n)]

for i in range(n):
    u[i][0], u[i][N] = f(x[i], y[0]),  f(x[i], y[N])
    u[0][i], u[N][i] = f(x[0], y[i]), f(x[N], y[i])

M = eps + 1
while eps < M:
    M = 0
    for i in range(1, N):
        for j in range(1, N):
            v = (u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]) / 4
            M = max(abs(u[i][j] - v), M)
            u[i][j] = v

np.set_printoptions(precision=1)
print(np.array(u))