from random import randint

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

def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    res, x1, y1 = extended_gcd(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return res, x, y

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

def Miller_Rabin(n, checks = 10):
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

def generate_prime(bit_length, is_prime):
    num = randint(2 ** (bit_length - 1) + 1, 2 ** bit_length)
    while not is_prime(num):
        num = randint(2 ** (bit_length - 1), 2 ** bit_length)
    return num

def sophie_prime(n):
    return Miller_Rabin(n) and n % 3 == 2 and n % 5 in (1, 3, 4) and Miller_Rabin(2 * n + 1)

def antiderivative_root(p):
    phi = p - 1
    for g in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]:
        if power(g, phi, p) == 1 and power(g, 2, p) != 1 and power(g, phi // 2, p) != 1:
            return g

class ElGamal:
    def __init__(self, bit_length):
        self.bit_length = bit_length
        self.g = generate_prime(bit_length, sophie_prime)
        self.p = 2 * self.g + 1
        self.x = generate_prime(bit_length, Miller_Rabin)
        self.y = power(self.g, self.x, self.p)

    def get_open_key(self):
        return (self.p, self.g, self.y)

    def send_message(self, target, text):
        p, g, y = target.get_open_key()
        message = 0
        for c in text:
            message = message * 100 + ord(c) - ord('a')
        if message > p:
            print('Too big!')
        else:
            k = generate_prime(self.bit_length, Miller_Rabin)
            a = power(g, k, p)
            b = power(y, k, p) * message % p
            #print(message, a, b)
            target.get_message((a, b))

    def get_message(self, ciphertext):
        a, b = ciphertext
        message = b * power(a, self.p - 1 - self.x, self.p) % self.p
        text = ''
        while message > 0:
            text += chr(message % 100 + ord('a'))
            message = message // 100
        print(text[::-1])

bit_length = 256

Masha, Jarik = ElGamal(bit_length), ElGamal(bit_length)
Jarik.send_message(Masha, 'hello')