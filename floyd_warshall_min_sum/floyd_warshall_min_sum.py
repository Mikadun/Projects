fin = open('input.txt', 'r')
stream = fin.read().split('\n');

n = int(stream.pop(0))
inf = 1000000
g = [[int(i) if int(i) != 0 else inf for i in stream.pop(0).split()] for _ in range(n)]
for k in range(n):
	for i in range(n):
		for j in range(n):
				g[i][j] = min(g[i][j], g[i][k] + g[k][j])
				
min_idx = 0
for i in range(n):
	print(' '.join([str(j) if j != inf else '0' for j in g[i]]))
	if sum(g[i]) < sum(g[min_idx]):
		min_idx = i

print( min_idx + 1 )