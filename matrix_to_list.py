n = int(input())
for j in [input().split() for _ in range(n)]:
	res = ''.join(list(map(lambda x, i: str(i + 1) + ' ' if x == '1' else '', j, range(n))))
	print(res if len(res) != 0 else '0')
