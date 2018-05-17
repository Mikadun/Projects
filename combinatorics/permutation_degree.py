n = int( input() )
permutation = [ int(i) - 1 for i in input().split() ]

zero_count = 0
lengths = []
used = [False] * n

def GCD(a, b):
	if a > b:
		a, b = b, a
	return b if a == 0 else GCD(a, b % a)

def LCM(a, b):
	return int(a * b / GCD(a, b))
	
def cycle_size():
	i = used.index(False)
	length = 0
	while not used[i]:
		used[i] = True
		i = permutation[i]
		length += 1

	return length

result = 1
while False in used:
		length = cycle_size()
		result = LCM( result, length )

print( result )