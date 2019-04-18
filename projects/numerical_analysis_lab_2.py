from math import log, factorial

f = lambda x: x*x + log(x) - 4
a, b = 1.5, 2
n = 10
h = (b - a) / n
x = [a + i * h for i in range(n + 1)]

# Узлы, в которых происходит подсчет

node_x = [1.52, 1.97, 1.77]

# div_diff - таблица разделенных разностей

div_diff = dict()

for i in range(len(x)):
    div_diff[(i, i)] = f(x[i])

for i in range(1, n + 1):
    for j in range(n - i + 1):
        div_diff[(j, j+i)] = (div_diff[(j+1, j+i)] - div_diff[(j, j+i-1)])/(x[j+i] - x[j])

# Разность между x0 и xi

def dx(x0, i):
    return x0 - x[i]

# Произведение разностей между x0 и xa...xb

def sum_dx(x0, a, b):
    res = 1
    for i in range(a, b + 1):
        res *= dx(x0, i)
    return res

# 1-я формула Ньютона

def L1(px, x0):
    res = f(x[x0])
    for i in range(1, n + 1):
        a, b = x0, x0 + i
        res += div_diff[(a, b)] * sum_dx(px, a, b - 1)
    return res

# 2-я формула Ньютона

def L2(px, x0):
    res = f(x[x0])
    for i in range(1, n + 1):
        a, b = x0 - i, x0
        res += div_diff[(a, b)] * sum_dx(px, a + 1, b)
    return res

# 1-я формула Гаусса

def L3(px, x0):
    res = f(x[x0])
    for i in range(1, n+1):
        a = x0 - i // 2
        b = x0 + i // 2 + i % 2
        res += div_diff[(a, b)] * sum_dx(px, a + (i + 1) % 2, b - i % 2)
    return res

# n-я производная функции, n >= 2

def df(px, n):
    return (-1)**(n + 1) * factorial(n) / px ** n

# Функция вычисления остаточного члена

def R(node, degree, mode = min):
    return mode([df(xi, degree) for xi in x]) * sum_dx(node, 0, degree - 1) / factorial(degree)

# Функция сравнения остаточных членов

def compare(node, degree, L, x0):
    print(abs(R(node, degree, min)))
    print(abs(L(node, x0) - f(node)))
    print(abs(R(node, n + 1, max)))
    print()

# Сравнение

compare(node_x[0], n + 1, L1, 0)
compare(node_x[1], n + 1, L2, n)
compare(node_x[2], n + 1, L3, n // 2)