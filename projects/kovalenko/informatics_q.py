d = {}
for i in range(int(input())):
    s = input().split()
    d.update(zip( s[1:], [s[0]] * (len(s) - 1) ))

print('\n'.join([d[input()] for _ in range(int(input()))]))