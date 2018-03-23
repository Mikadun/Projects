n = int(input())
inf = 1000000
g = [[int(i) if int(i) != 0 else inf for i in input().split()] for _ in range(n)]
for k in range(n):
  for i in range(n):
    for j in range(n):
    	  g[i][j] = min(g[i][j], g[i][k] + g[k][j])
for i in g:
	print(" ".join(["1" if j != inf else "0" for j in i]))
