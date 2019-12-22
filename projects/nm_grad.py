import numpy as np
np.set_printoptions(precision=2, suppress=True)

n = 4

A = np.matrix([
    [10.9, 1.2, 2.1, 0.9],
    [1.2, 11.2, 1.5, 2.5],
    [2.1, 1.5, 9.8, 1.3],
    [0.9, 2.5, 1.3, 12.1]
])

b = np.array([-7.0, 5.3, 10.3, 24.6])
x = np.array([-1, 0, 1, 2])
#print(x)

x = np.array([0.0] * n)

for k in range(100):
  temp = (x*A-b)
  delta = (temp * temp.T).item() / (temp * (A * temp.T)).item()
  x = x - delta*(temp)


print(x)