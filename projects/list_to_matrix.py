n = int(input())
edges = [input().split() for _ in range(n)]
graph = [['0' for _ in range(n)] for __ in range(n)]
for i in range(n):
	for j in edges[i]:
	  if(j != '0'):
	    graph[i][int(j) - 1] = '1'
for i in graph:
  print(" ".join(i))
