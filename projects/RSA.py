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
    if n % 2 == 0:
        return False

    for divisor in range(1, ceil(sqrt(n) + 1), 2):
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

def Miller_Rabin(n, checks = 30):
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

class RSA:
    def __init__(self, bit_length):
        self.is_prime = Miller_Rabin
        p, q = self.generate_prime(bit_length), self.generate_prime(bit_length)
        fi = (p - 1) * (q - 1)
        self.key_public = self.generate_public(fi)
        self.key_private = self.generate_secret(self.key_public, fi)
        self.module = p * q

    def generate_prime(self, bit_length):
        num = randint(2 ** (bit_length - 1), 2 ** bit_length)
        while not self.is_prime(num):
            num = randint(2 ** (bit_length - 1), 2 ** bit_length)
        return num

    def generate_public(self, fi):
        max_length = len(str(fi)) - 2
        while True:
            length = randint(max_length // 2, max_length)
            one_bit_amount = length // 10
            num = (1 << length) + 1
            for i in range(one_bit_amount):
                num |= (1 << randint(1, length - 1))
                if gcd(num, fi) == 1:
                    return num
        

    def generate_secret(self, public, fi):
        d = extended_gcd(self.key_public, fi)[1]
        if d < 0:
            d += fi
        return d

    def encode(self, message, key = None):
        result = ''
        for c in message:
            result += str(power(ord(c), self.key_public, self.module)) + ' '

        return result
    
    def decode(self, message):
        result = ''
        for c in message.split():
            result += chr(power(int(c), self.key_private, self.module))

        return result

rsa = RSA(128)
code = rsa.encode('Hello, world!')
decode = rsa.decode(code)
print(code, decode)