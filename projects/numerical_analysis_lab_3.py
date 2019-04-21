from math import log, factorial

f = lambda x: x*x + log(x) - 4
a, b = 1.5, 2
n = 10
h = (b - a) / n
x = [a + i * h for i in range(n + 1)]

# Узлы, в которых происходит подсчет

node_x = x[2]

# Разность между x0 и xi

def dx(x0, i):
    return x0 - x[i]

# Произведение разностей между x0 и xa...xb, исключая xk

def sum_dx(x0, a, b, skip = -1):
    res = 1
    for i in range(a, b + 1):
        if i != skip:
            res *= dx(x0, i)
    return res

# Производная f(x) в точке px

def df(px, n):
    if n == 1:
        return 2 * px + 1 / px
    if n == 2:
        return 2 - 1 / px ** 2
    return (-1)**(n + 1) * factorial(n) / px ** n

# Производная вшита, так что только для n = 3

def dL(px, n):
    koef_1 = lambda a, b, k: sum([x[i] if i != k else 0 for i in range(a, b + 1)])

    def koef_2(a, b, k):
        ixs = [x[i]  for i in list(filter(lambda x: x != k, list(range(a, b + 1))))]
        return ixs[0]*ixs[1] + ixs[0]*ixs[2] + ixs[1]*ixs[2]

    res = 0
    for k in range(n + 1):
        res += f(x[k]) * (3 * px * px - 2 * px * koef_1(0, n, k) + koef_2(0, n, k)) / sum_dx(x[k], 0, n, k)
    return res

# Функция вычисления остаточного члена

def R(node, degree, mode = min):
    return mode([df(xi, degree) for xi in x]) * sum_dx(node, 0, degree - 1, 2) / factorial(degree)

# Функция сравнения остаточных членов

def compare(node, degree, L):
    print(R(node, degree + 1, min))
    print(abs(L(node, degree) - df(node, 1)))
    print(R(node, degree + 1, max))
    print()

# Сравнение

compare(x[2], 3, dL)