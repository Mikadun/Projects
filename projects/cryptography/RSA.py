from math import ceil, sqrt
from random import randint
import matplotlib.pyplot as plt
from timeit import timeit
import time

def power(n, p, mod):
    if p == 1:
        return n
    n %= mod
    t = 1

    while p > 0:
        if p & 1:
            t = (t * n) % mod
        n = (n * n) % mod 
        p = p >> 1

    return t

def trial_division(n):
    if n < 2:
        raise Exception('Value error: number must be greater than 1')
    if n % 2 == 0:
        return False

    for divisor in range(1, ceil(sqrt(n) + 1), 2):
        if n % divisor == 0:
            return False
    return True

def Miller_iteration(d, n):
    a = randint(3, n - 2)
    a_exp_d = power(a, d, n)
    
    if a_exp_d == 1 or a_exp_d == n - 1:
        return True
    
    while d != n - 1:
        a_exp_d = (a_exp_d ** 2) % n
        d *= 2
        if a_exp_d == 1:
            return False

        if a_exp_d == n - 1:
            return True
    return False

def Miller_Rabin(n, checks = 30):
    if n <= 1:
        return False

    if n <= 3:
        return True
    
    if n % 2 == 0:
        return False

    d = n - 1
    while d % 2 == 0:
        d //= 2

    for check in range(checks):
        if not Miller_iteration(d, n):
            return False

    return True

def gcd(a, b):
    while b:
        a %= b
        a, b = b, a
    return a

def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    res, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return res, x, y

def Jacobi(n, m):
    s = 1
    if gcd(n, m) != 1:
        return 0

    while True:
        n = n % m
        k = 0
        while n % 2 == 0:
            n = n >> 1
            k += 1
        k %= 2
        
        if k == 1 and (m % 8 == 3 or m % 8 == 5):
            s *= -1
        
        if n == 1 or (n == m - 1 and m % 4 == 1):
            return s

        if n == m - 1 and m % 4 == 3:
            return -s

        n, m = m, n
        if (n - 1) % 4 and (m - 1) % 4:
            s *= -1

def Solovay_Strassen(n, checks = 30):
    if n % 2 == 0:
        return False

    if n % 3 == 0:
        return False

    for _ in range(checks):
        a = randint(3, n - 1)
        if power(a, (n - 1) // 2, n) != (Jacobi(a, n) % n):
            return False
    return True


def rsa(bit_length, is_prime = Miller_Rabin):
    p, q = generate_prime(bit_length, is_prime), generate_prime(bit_length, is_prime)
    fi = (p - 1) * (q - 1)
    e = generate_public(fi)
    d = generate_secret(e, fi)
    n = p * q
    return (e, n), (d, n)

def generate_prime(bit_length, is_prime):
    num = randint(2 ** (bit_length - 1) + 1, 2 ** bit_length)
    while not is_prime(num):
        num = randint(2 ** (bit_length - 1), 2 ** bit_length)
    return num

def generate_public(fi):
    max_length = len(str(fi)) - 2
    while True:
        length = randint(max_length // 2, max_length)
        if length < 3:
            length = max_length
        one_bit_amount = length // 10
        if one_bit_amount < 3:
            one_bit_amount = 2

        num = (1 << length) + 1
        for i in range(one_bit_amount):
            num |= (1 << randint(1, length - 1))
            if gcd(num, fi) == 1:
                return num
    

def generate_secret(e, fi):
    d = extended_gcd(e, fi)[1]
    if d < 0:
        d += fi
    return d

def encode(message, public_key):
    result = ''
    for c in message:
        result += str(power(ord(c), public_key[0], public_key[1])) + ' '

    return result

def decode(message, private_key):
    result = ''
    for c in message.split():
        result += chr(power(int(c), private_key[0], private_key[1]))

    return result

def lineplot(ax, x_data, y_data, x_label="", y_label="", color="#539caf"):
    ax.plot(x_data, y_data, lw = 2, color=color, alpha = 1)
    ax.set_xlabel(x_label)
    ax.set_ylabel(y_label)

_range = range(5, 11)
_, ax = plt.subplots()
ax.set_title('RSA: comparasion of prime test algorithms')

def test(_range, ax, algorithm, color='blue'):
    times = []

    for i in _range:
        t = time.time()
        rsa(2 ** i, algorithm)
        times.append(time.time() - t)
    lineplot(ax, _range, times, y_label = 'seconds', x_label = 'length: 2^', color=color)

test(_range, ax, Miller_Rabin, 'red')
test(_range, ax, Solovay_Strassen, 'blue')
plt.show()
