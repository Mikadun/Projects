n = int(input())
graph = [input().split() for _ in range(n)]
edges = [[] for _ in range(n)]
for i in range(n):
  for j in range(n):
  	if graph[i][j] != '0':
  	  edges[i].append(j + 1)
  if edges[i] == []:
    edges[i] = [0]
for i in edges:
  print(" ".join([str(j) for j in i]))
