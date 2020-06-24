from sympy import *
import numpy as np
'''
a, b = 0, 1
n = 1
l = -0.5
s, x = var('s x')
f = 5 * x / 6
alpha = [x]
beta = [-s * l]
fi = [float(integrate(beta[i] * f.subs({x: s}), (s, a, b))) for i in range(n)]
A = [[integrate(alpha[j].subs({x: s}) * beta[i].subs({x: s}), (s, a, b)) for i in range(n)] for j in range(n)]
C = np.array([[float(int(i == j) - A[i][j]) for i in range(n)] for j in range(n)])
C = np.linalg.solve(C, fi)
u = f + sum([C[i] * alpha[i] for i in range(n)])
print(u)

'''
from sympy import *
import numpy as np


a, b = 0, 1
n = 3
s, x = var('s x')
f = 0.5 / sqrt(x)
alpha = [x, x**3, x**5]
beta = [-0.6 * s**0, 0.6**3 * s**2 / factorial(3), -0.6**5 * s**4 / factorial(5)]
fi = [float(integrate(beta[i] * f.subs({x: s}), (s, a, b))) for i in range(n)]
A = [[integrate(alpha[j].subs({x: s}) * beta[i].subs({x: s}), (s, a, b)) for i in range(n)] for j in range(n)]
C = np.array([[float(int(i == j) - A[i][j]) for i in range(n)] for j in range(n)])
C = np.linalg.solve(C, fi)
u = f + sum([C[i] * alpha[i] for i in range(n)])
print(u)
