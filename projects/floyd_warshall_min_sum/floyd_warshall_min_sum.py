fin = open('input.txt', 'r')
stream = fin.read().split('\n');

n = int(stream.pop(0))
students = [int(i) for i in stream.pop(0).split()]
inf = 1000000
g = [[int(i) if int(i) != 0 else inf for i in stream.pop(0).split()] for _ in range(n)]
for i in range(n):
	g[i][i] = 0

# Floyd-Warshall
for k in range(n):
	for i in range(n):
		for j in range(n):
			g[i][j] = min(g[i][j], g[i][k] + g[k][j])
				
min_idx = 0
min_sum = inf

# Min sum search alg
for i in range(n):
	# print(' '.join([str(j) if j != inf else '0' for j in g[i]]))

	# cur_sum = sum( g[i][j] * students[j] ) for j in range(n)
	cur_sum = sum(list(map(lambda x, y: x * y, students, g[i])))

	if cur_sum < min_sum:
		min_idx = i
		min_sum = cur_sum

print( min_idx + 1 )
