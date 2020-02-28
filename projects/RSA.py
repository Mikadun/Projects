from math import ceil, sqrt
from random import randint

def power(n, p, mod):
    # Rapid exponentiation
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
    # Check if n is prime
    if n < 2:
        raise Exception('Value error: number must be greater than 1')

    for divisor in range(2, ceil(sqrt(n) + 1)):
        if n % divisor == 0:
            return False
    return True

def Miller_iteration(d, n):
    a = randint(2, n - 2)
    a_exp_d = power(a, d, n)
    
    # First condition
    if a_exp_d == 1 or a_exp_d == n - 1:
        return True
    
    while not d == n - 1:
        a_exp_d = a_exp_d ** 2
        d *= 2
        if a_exp_d == n - 1:
            return True
    return False

def Miller_Rabin(n, checks = 10):
    if n == 3:
        return True
    if n % 2 == 0:
        return False

    d = n - 1
    while not d & 1:
        d = d >> 1

    for check in range(checks):
        if not Miller_iteration(d, n):
            return False

    return True
