n = 5
N = n - 1
A = [ 0, -1,   2,  1,   2]
B = [ 4,  4,   2,  1,   3]
C = [ 1,  1,  -1,  2,   0]
F = [11, -5,  10,  -4, -13]

alpha, beta = [0] * n, [0] * n

alpha[1] = -C[0] / B[0]
beta[1]  =  F[0] / B[0]

for k in range(1, n - 1):
    alpha[k + 1] = -C[k] / (B[k] + A[k] * alpha[k]) 
    
for k in range(1, n - 1):
	beta[k + 1]  = (F[k] - A[k] * beta[k]) / (B[k] + A[k] * alpha[k])
    
U = [0 for k in range(n)]
U[N] = (F[N] - A[N] * beta[N]) / (A[N] * alpha[N] + B[N])

for k in range(N - 1, 0, -1):
    U[k] = alpha[k + 1] * U[k + 1] + beta[k + 1]
    
print(' '.join([str(round(i, 2)) for i in U]))
    
    