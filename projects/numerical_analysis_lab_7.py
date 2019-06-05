from math import log
f = lambda x: 2**x - x**2 - 1
df = lambda x: log(2) * 2**x - 2*x
d2f = lambda x: log(2)**2 * 2**x - 2
eps = 0.0001

def separate_roots(a, b):
	i = a
	step = 0.48
	borders = []
	while i < b:
		if f(i) * f(i + step) < eps:
			borders.append((i, i + step))
		i += step
	return borders

def find(a, b, forward = True):
	x_1 = [a] if forward else [b]
	x_2 = [b] if forward else [a]
	while abs(x_1[-1] - x_2[-1]) > eps:
		x_2.append(x_2[-1] - (f(x_2[-1])*(x_1[-1] - x_2[-1]))/(f(x_1[-1])-f(x_2[-1])))
		x_1.append(x_1[-1] - f(x_1[-1]) / df(x_1[-1]))

	return round(x_1[-1], 5)

def find_all_positive(right_max):
	roots = []
	borders = separate_roots(0 - eps, right_max)

	for border in borders:
		a, b = border[0], border[1]
		if df(a) * d2f(a) < 0:
			roots.append(find(a, b))
		else:
			roots.append(find(a, b, False))
	return roots

print(find_all_positive(20))

