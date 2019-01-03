
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

  return (True, 'Ok', x, y)

class Vector:
  def __init__(self, x1, y1, x2 = None, y2 = None):
    if x2 != None:
      self.x = abs(x2 - x1)
      self.y = abs(y2 - y1)
    else:
      self.x = x1
      self.y = y1
  
  def length(self):
    return (self.x**2 + self.y**2)**(0.5)
  
  def normalize(self):
    if self.length():
      self.x = self.x / self.length()
      self.y = self.y / self.length()
    return self

  def __eq__(self, other):
    return self.x == other.x and self.y == other.y

  def __neg__(self):
    return Vector(-self.x, -self.y)


def check_same(x1, y1, x2, y2, x3, y3, x4, y4):
  v1 = Vector(x1, y1, x2, y2).normalize()
  v2 = Vector(x3, y3, x4, y4).normalize()
  return v1 == v2 or v1 == -v2

def cross_point_in_range(x1, y1, x2, y2, x3, y3, x4, y4):
  if check_same(x1, y1, x2, y2, x3, y3, x4, y4):
    return (True, 'On one line', x3, y3)
  cp = cross_point(x1, y1, x2, y2, x3, y3, x4, y4)
  if cp[0] :
    x, y = cp[1], cp[2]
    if min(x1, x2) <= x <= max(x1, x2) and min(x3, x4) <= x <= max(x3, x4):
      if min(y1, y2) <= y <= max(y1, y2) and min(y3, y4) <= y <= max(y3, y4):
        return (cp)
  return (False, 'Not in range', 0, 0)

n = int(input())
lines = []
for _ in range(n):
  line = [int(i) for i in input().split()]
  lines.append(sorted([line[:2], line[2:]]))

lines = sorted(lines)
#print(lines)

for i in range(len(lines) - 1):
  for j in range(i + 1, len(lines)):
    p1 = lines[i][0]
    p2 = lines[i][1]
    p3 = lines[j][0]
    p4 = lines[j][1]
    res = cross_point_in_range(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1])
    if res[0]:
      print('Lines', (p1, p2), (p3, p4), 'intersect in', [res[2], res[3]])
