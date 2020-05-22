with open('input.txt') as f:
    d = {}
    for line in f.readlines():
        name, item, count = line.split()
        if name in d.keys():
            if item in d[name].keys():
                d[name][item] += int(count)
            else:
                d[name][item] = int(count)
        else:
            d[name] = {item: int(count)}

    for name, items in sorted(d.items()):
        print('{}:'.format(name))
        for item, count in sorted(items.items()):
            print(item, str(count))