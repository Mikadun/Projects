
def sorted2(data, key = lambda x: -x):
    return sorted([sorted(x, key = key) for x in data], key = lambda x: key(x[-1]))

print(sorted2([[6, 5, 4], [3, 2], [1]], key = lambda x: x))
