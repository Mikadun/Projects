d = {}
for i in range(int(input())):
    val, keys = input().split(' - ')
    for key in keys.split(', '):
        if key in d.keys():
            d[key].append(val)
        else:
            d[key] = [val]
    
print(len(d.keys()))
print('\n'.join([ k + ' - ' + ', '.join(sorted(v)) for k, v in sorted(d.items()) ]))