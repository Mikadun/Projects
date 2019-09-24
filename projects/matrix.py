import numpy as np
print()

for n in range(3, 8):
	A = np.array([ [ 0 if j < i else 1 if j == i else -1 for j in range(n)] for i in range(n)])
	N = np.array([ [ 1 if j <= i else -1 for j in range(n)] for i in range(n)])
	b = np.array([-1] * n)
	eps = 1e-6
	print('#' * 10, n, '#' * 10)
	print()
	for i in range(1, 5):
		m = (A + eps * N)
		res = np.linalg.solve(m, b)
		print(res)
		eps *= 10
	print()