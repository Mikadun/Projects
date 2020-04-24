
def in_borders(pair):
    return 1 <= pair[1] <= 8 and ord('A') <= pair[0] <= ord('H')

moves = [(1 * i, 2 * j) for i, j in zip([1, 1, -1, -1], [1, -1, 1, -1])]
moves = sorted(moves + [(2 * i, 1 * j) for i, j in zip([1, 1, -1, -1], [1, -1, 1, -1])])

def list_of_turns(cell):
    pair = ( ord(cell[0]), int(cell[1]) )
    pairs = filter(in_borders, map(lambda x: (x[0] + pair[0], x[1] + pair[1]), moves))
    return [chr(i) + str(j) for i, j in pairs]

print(list_of_turns('B1'))