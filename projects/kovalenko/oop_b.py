from numbers import Number as num

class MyVector:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def __add__(self, other):
        if isinstance(other, MyVector):
            return MyVector(self.x + other.x, self.y + other.y)
        else:
            raise('Unsupported operator+ for vector and nonvector')

    def __iadd__(self, other):
        if isinstance(other, MyVector):
            self.x += other.x
            self.y += other.y
            return self
        else:
            raise('Unsupported operator+ for vector and nonvector')
    
    def __neg__(self):
        return MyVector(-self.x, -self.y)
    
    def __sub__(self, other):
        if isinstance(other, MyVector):
            return MyVector(self.x - other.x, self.y - other.y)
        else:
            raise('Unsupported operator- for vector and nonvector')
    
    def __isub__(self, other):
        if isinstance(other, MyVector):
            self.x -= other.x
            self.y -= other.y
            return self
        else:
            raise('Unsupported operator- for vector and nonvector')

    def __mul__(self, val):
        if isinstance(val, num):
            return MyVector(self.x * val, self.y * val)
        else:
            raise('Unsupported operator* for vector and non number object')
    
    def __rmul__(self, val):
        return self.__mul__(val)

    def __imul__(self, val):
        if isinstance(val, num):
            self.x *= val
            self.y *= val
            return self
        else:
            raise('Unsupported operator* for vector and non number object')

    def __eq__(self, other):
        if isinstance(other, MyVector):
            return self.x == other.x and self.y == other.y
        else:
            raise('Unsupported operator== for vector and nonvector')
    
    def __ne__(self, other):
        return not self.__eq__(other)
    
    def len(self):
        return (self.x ** 2 + self.y ** 2) ** 0.5

    def __len__(self):
        return int(self.len())

    def __str__(self):
        return 'MyVector({}, {})'.format(self.x, self.y)

v1 = MyVector(1, 1.2)
v2 = MyVector(2.2, -3.4)
#print(v1 + v2)
#print(v1 - v2)
#print(v1 * 2)
#print(2 * v2)
#v1 += v2
#print(v1)
#v1 -= v2
#print(v1)
#v1 *= 3
#print(v1)
#print(v1 == v2)
#print(v1 != v2)