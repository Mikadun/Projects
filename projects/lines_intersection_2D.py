
'''
(y - y1)/(y2 - y1) = (x - x1)/(x2 - x1)
y - y1 = (x - x1)(y2 - y1)/(x2 - x1)
y = (x - x1)(y2 - y1)/(x2 - x1) + y1
y = (x(y2 - y1) - x1(y2 - y1))/(x2 - x1) + y1
y = x(y2 - y1)/(x2 - x1) - x1(y2 - y1)/(x2 - x1) + y1

#
x = (y - y1)(x2 - x1)/(y2 - y1) + x1
#

x(y2 - y1)/(x2 - x1) - x1(y2 - y1)/(x2 - x1) + y1 =
= x(y4 - y3)/(x4 - x3) - x1(y4 - y3)/(x4 - x3) + y3

x(y2 - y1)/(x2 - x1) - x(y4 - y3)/(x4 - x3) = x1(y2 - y1)/(x2 - x1) - x1(y4 - y3)/(x4 - x3) - y1 + y3

x((y2 - y1)/(x2 - x1) - (y4 - y3)/(x4 - x3)) = x1(y2 - y1)/(x2 - x1) - x1(y4 - y3)/(x4 - x3) - y1 + y3

x = (x1(y2 - y1)/(x2 - x1) - x1(y4 - y3)/(x4 - x3) - y1 + y3)/((y2 - y1)/(x2 - x1) - (y4 - y3)/(x4 - x3))

'''

def cross_point(x1, y1, x2, y2, x3, y3, x4, y4):
  if x1 == x2 or x3 == x4:
      if x1 == x2:
        y = (x1 - x3)*(y4 - y3)/(x4 - x3) + y3
      else:
        y = (x3 - x1)*(y2 - y1)/(x2 - x1) + y1
      return (True, x1 if x1 == x2 else x3, y)
  
  if y1 == y2 or y3 == y4:
      if y1 == y2:
        x = (y1 - y3)*(x4 - x3)/(y4 - y3) + x3
      else:
        x = (y3 - y1)*(x2 - x1)/(y2 - y1) + x1
      return (True, x, y1 if y1 == y2 else y3)
        
  x = (x1*(y2 - y1)/(x2 - x1) - x3*(y4 - y3)/(x4 - x3) - y1 + y3)/((y2 - y1)/(x2 - x1) - (y4 - y3)/(x4 - x3))

  y = (x - x1)*(y2 - y1)/(x2 - x1) + y1

  return (True, x, y)

class Vector:
  def __init__(self, x1, y1, x2, y2):
    self.x = x2 - x1
    self.y = y2 - y1
  
  def length(self):
    return (self.x**2 + self.y**2)**(0.5)
  
  def normalize(self):
    if self.length():
      self.x = self.x / self.length()
      self.y = self.y / self.length()
    return self

  def __eq__(self, other):
    return self.x == other.x and self.y == other.y

def check_same(x1, y1, x2, y2, x3, y3, x4, y4):
  v1 = Vector(x1, y1, x2, y2).normalize()
  v2 = Vector(x3, y3, x4, y4).normalize()
  if v1 == v2:
    if min(x1, x2) <= min(x3, x4) <= max(x1, x2) and min(y1, y2) <= min(y3, y4) <= max(y1, y2):
      return (True, (True, min(x3, x4), min(y3, y4)))
    else:
      return (True, (False, 0, 0))
  return (False, (False, 0, 0))

def cross_point_in_range(x1, y1, x2, y2, x3, y3, x4, y4):
  on_line = check_same(x1, y1, x2, y2, x3, y3, x4, y4)
  if on_line[0]:
    print('On the same line', end=' ')
    return on_line[1]
  cp = cross_point(x1, y1, x2, y2, x3, y3, x4, y4)
  if cp[0] :
    x, y = cp[1], cp[2]
    if min(x1, x2) <= x <= max(x1, x2) and min(x3, x4) <= x <= max(x3, x4):
      if min(y1, y2) <= y <= max(y1, y2) and min(y3, y4) <= y <= max(y3, y4):
        return (cp)
    print('Not in range', end=' ') 
  return (False, 0, 0)
      

print(cross_point_in_range(0, 4, 4, 0, 0, 0, 4, 4))
print(cross_point_in_range(-1, -1, 4, 4, -2, 2, 4, 0))
print(cross_point_in_range(1, 1, 1, 4, 3, 1, 3, 4))
print(cross_point_in_range(1, 2, 3, 2, 2, 1, 2, 3))
print(cross_point_in_range(1, 1, 3, 1, 1, 3, 3, 3))
print(cross_point_in_range(7, 1, 1, 5, 1, 3, 6, 3))
print(cross_point_in_range(-3, 0, 1, 2, 3, 1, 3, 6))
print(cross_point_in_range(-1, -2, 1, 1, 1, 1, 3, 4))
print(cross_point_in_range(1, -1, 1, 1, 1, 2, 1, 4))
