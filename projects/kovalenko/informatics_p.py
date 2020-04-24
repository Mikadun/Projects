with open('input.txt') as f:
    d = {}
    for word in f.read().split():
        if word in d.keys():
            d[word] += 1
        else:
            d[word] = 1
    d2 = {}
    for word in d.keys():
        if d[word] in d2.keys():
            d2[d[word]].append(word)
        else:
            d2[d[word]] = [word]
    print( '\n'.join([ '\n'.join(sorted(pair[1])) for pair in sorted(d2.items(), reverse = True) ]) )