import numpy as np
np.set_printoptions(precision=2, suppress=True)

N = 10
n = N + 1
h = 1 / N
tau = 1 / N
a = 1 / 2
c1 = a * tau / h
k = c1 ** 2
c2 = 2 * (1 - k)

rx = [i * h for i in range(n)]
rt = [i * tau for i in range(n)]

gamma0 = lambda t: -3 * t
gamma1 = lambda t: t ** 2

u = np.zeros(shape=(n, n))

for j in range(1, N):
    u[0, j + 1] = gamma0(rt[j + 1])
    u[N, j + 1] = gamma1(rt[j + 1])

    for i in range(1, N):
        u[i, j + 1] = c2 * u[i, j] + k * (u[i + 1, j] + u[i - 1, j]) - u[i, j - 1]

print(u)