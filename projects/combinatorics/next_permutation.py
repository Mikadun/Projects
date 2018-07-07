n = int(input())
permutation = [int(i) for i in input().split()]
i = n - 2
while permutation[i] > permutation[i+1] and i > 0:
	i -= 1
idx = permutation.index( min( permutation[i+1:] ) )
permutation[i], permutation[idx] = permutation[idx], permutation[i]
permutation[i+1:] = sorted(permutation[i+1:])
print(' '.join([str(i) for i in permutation]))