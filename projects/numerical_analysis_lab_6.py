
from math import log, cos, sin
import os
import matplotlib.pyplot as plt

def save(name='', fmt='png'):
    pwd = os.getcwd()
    iPath = './pictures/{}'.format(fmt)
    if not os.path.exists(iPath):
        os.mkdir(iPath)
    os.chdir(iPath)
    plt.savefig('{}.{}'.format(name, fmt), fmt='png')
    os.chdir(pwd)

a, b = 1, 10
n = 20
h = (b - a) / n
w = [a + i*h for i in range(n)]
f = lambda x: log(x) + x - 4 + cos(x)
df = lambda x: -sin(x) + 1 + 1 / x
d2f = lambda x: -cos(x) - 1 / x**2

def solve_linear_system(A, B, C, F):
	n = len(B)
	N = n - 1

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
	    
	#print(' '.join([str(round(i, 2)) for i in U]))
	return U

def spline(x):
	N = n - 1
	y = [f(x) for x in w]
	u, v = 0.5, 0.5
	d2y0 = d2f(y[0])
	d2yN = d2f(y[N])

	A = [u] * n
	B = [2] * n
	C = [v] * n
	A[0] = 0
	C[0] = 1
	A[N] = 1
	C[N] = 0

	F = [0] * n
	F[0] = 3 * (y[1] - y[0]) / h - h * d2y0 / 2
	F[N] = h * d2yN / 2 + 3 * (y[N] - y[N - 1]) / h
	for i in range(1, N):
		F[i] = 3*(v*(y[i+1] - y[i])/h + v*(y[i] - y[i-1])/h)

	m = solve_linear_system(A, B, C, F)

	i = int((x - a) / h)
	def dS(x, i):
		second_p = 2*(x - w[i])*(3*(y[i+1] - y[i]) - h*(m[i+1] + 2*m[i])) / h**2
		third_p = 3*((x - w[i])**2)*(h*(m[i+1] + m[i]) - 2*(y[i+1] - y[i])) / h**3
		return m[i] + second_p + third_p

	return dS(x, i)

print(spline(1.8))

fig = plt.figure()
plt.plot(w, [df(x) for x in w], color='red')
plt.plot(w, [spline(w[i]) for i in range(n-1)]+[df(w[-1])], color='blue')
plt.grid(True)
save('1')
plt.show()