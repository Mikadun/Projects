def bfs(g, start, n):
	used = [False] * n
	used[start] = True
	deck = [start]
	res = []
	while len(deck):
		v = deck.pop()
		for i in range(n):
			if (not used[i]) and g[v][i]:
			  deck.append(i)
			  used[i] = True
		res.append(v)
	for i in res:
	  g[start][i] = 1

size = int(input())
graph = [[int(i) for i in input().split()] for _ in range(size)]
for i in range(size):
  bfs(graph, i, size)

for i in graph:
  print(" ".join([str(j) for j in i]))
