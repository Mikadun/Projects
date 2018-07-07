number = int(input())
used = [0] * number
result = []
def term( n, high, depth ):
  if( n == 0 ):
    result.append( used[:used.index(0)] if 0 in used else used[0:] )
    return
  high = min( n, high )
  for i in range(1, high + 1):
    used[depth] = i
    term( n - i, i, depth + 1 );
  used[depth] = 0
    
term(number, number, 0);

for i in result:
	i.sort()

result.sort(reverse=True)

for i in result:
	print( ' '.join([ str(j) for j in i ]) )