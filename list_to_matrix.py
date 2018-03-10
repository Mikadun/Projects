n = int(input())
for _ in range(n):
	stream = input().split()
	print(" ".join([str(int(str(i + 1) in stream)) for i in range(n)]))
