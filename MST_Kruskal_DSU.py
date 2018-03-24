from operator import itemgetter
n, m = [int(i) for i in input().split()]
edges = [[int(i) for i in input().split()] for _ in range(m)]
edges = sorted(edges, key=itemgetter(2), reverse = True)
p = [i for i in range(n)]
r = [0] * n;

def find_dsu( x ):
	return x if x == p[x] else find_dsu( p[x] )

def union_dsu( x, y ):
	tx = find_dsu( x )
	ty = find_dsu( y )
	if r[tx] < r[ty]:
		p[tx] = ty
	elif:
		p[ty] = tx
		if r[tx] == r[ty]:
			r[tx] += 1

result = 0
while(len(edges) > 0):
	edge = edges.pop()
	if find_dsu(edge[0] - 1) != find_dsu(edge[1] - 1):
		result += edge[2]
		union_dsu( edge[0] - 1, edge[1] - 1)
print(result)
