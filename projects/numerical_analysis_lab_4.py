from math import log, factorial

f = lambda x: x*x + log(x) - 4
a, b = 1.5, 2
n = 10
get_h = lambda degree: (b - a) / (n * degree)

i = 1

def I(i):
    h = get_h(i)
    return sum([f(a + h * (j + 0.5)) for j in range(i * n - 1)]) * h

EPS = 1e-10

while True:
    I1 = I(i)
    I2 = I(i + 1)
    i *= 2
    if abs(I1 - I2) < EPS:
        print(i)
        print(I1)
        break
