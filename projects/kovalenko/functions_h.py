
def sorted2(data, key = None):
    if key == None:
        return sorted([sorted(x, reverse = True) for x in data], key = lambda x: x[-1], reverse = True)
    return sorted([sorted(x, key = key) for x in data], key = lambda x: key(x[-1]))

print(sorted2([[6, 5, 4], [3, 2], [1]], key = lambda x: x))
