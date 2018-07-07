# naive realization O(n^3)
n = int(input())
g = [[int(i) for i in input().split()] for _ in range(n)]
used = [False] * n
used[0] = True
tree = [0]
res = []
while(False in used):
	minimum = 100000
	index = [0, 0]
	for i in tree:
		for j in range(n):
			if g[i][j] == 0:
				continue
			if minimum > g[i][j] and not used[j]:
				minimum = g[i][j]
				index = [i, j]
	used[index[1]] = True
	tree.append(index[1])
	res.append([index[0], index[1]])
res.sort()
for i in res:
  print(i[0] + 1, i[1] + 1)
