fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

p, n = [ int(i) for i in fin.readline().split() ]
n += 1

C = [ int( fin.readline().strip() ) for i in range(n) ]
A = [ 0 for i in range(n) ] 
A[0] = C[0]

for i in range( n - 1 ):
  for j in range( i + 1, 0, -1 ):
    A[j] = ( A[j] + A[j - 1] * C[i + 1] ) % p

for i in range( 1, n, 2 ):
  A[i] = ( p - A[i] ) % p

fout.write( ' '.join([ str(A[ n - i - 1 ]) for i in range(n) ]))

fin.close()
fout.close()
