class Polynomial:
    def __init__(self, koefs):
        self.koefs = koefs.copy()

    def __add__(self, other):
        min_length, max_length = sorted((len(self.koefs), len(other.koefs)))
        biggest = self.koefs if len(self.koefs) == max_length else other.koefs
        return Polynomial([x + y for x, y in zip(self.koefs, other.koefs)] + biggest[min_length:])

    def __call__(self, val):
        return sum([k * (val ** i) for i, k in zip(range(len(self.koefs)), self.koefs)])

p1 = Polynomial([1, 1, 1])
p2 = Polynomial([-2, 1])
p3 = p1 + p2
print(p3.koefs)
print(p3(2))