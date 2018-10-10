
class Koef:
  
  def __init__(self, val):
    self.val = val

  def __add__(self, koef):
    if self.val != '':
      return Koef(self.val + ' + ' + koef.get())
    else:
      return Koef( koef.get() )
  
  def __mul__(self, koef):
    if self.val != '':
      values = self.val.split(' + ')
      values = list( map( lambda x: x + ' * ' + koef.get(), values ) )
      return Koef(' + '.join(values))
    else:
      return Koef( koef.get() )
  
  def get(self):
    return self.val
    
fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

p, n = [ int(i) for i in fin.readline().split() ]
n += 1

C = [ Koef( fin.readline().strip() ) for i in range(n) ]
A = [ Koef('') for i in range(n) ] 
A[0] = C[0]

for i in range(n - 1):
  for j in range( i + 1, 0, -1 ):
    temp = A[j - 1] * C[i + 1]
    A[j] = A[j] + temp

fout.write( '\n'.join([i.get() for i in A]))

fin.close()
fout.close()

