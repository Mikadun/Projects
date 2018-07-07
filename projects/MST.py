n = int(input())
edges = []
count = 0
for j in [input().split() for _ in range(n)]:
	edges += list(map(lambda x, i: [int(x), count, i] if x != '0' else [], j, range(n)))
	count += 1
edges.sort(reverse=True)
while(edges[-1] == []):
	edges.pop()
trees = [i for i in range(n)]
result = []
while(len(edges) > 0):
	edge = edges.pop()
	if trees[edge[1]] != trees[edge[2]]:
		new_tree = trees[edge[1]]
		old_tree = trees[edge[2]]
		result.append(list(map(lambda x: x + 1, edge[1:3])))
		for i in range(n):
			if trees[i] == old_tree:
				trees[i] = new_tree
result.sort()
for i in result:
	print(" ".join([str(j) for j in i]))
