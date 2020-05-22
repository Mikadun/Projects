relationship = dict([tuple(input().split()) for _ in range(int(input()) - 1)])
heights = {}

def find_height(name):
    if name in heights.keys():
        return heights[name]
    else:
        if name in relationship.keys():
            height = find_height(relationship[name]) + 1
            heights[name] = height
            return height
        else:
            heights[name] = 0
            return 0

for name in relationship.keys():
    find_height(name)

print('\n'.join([person + ' ' + str(height) for person, height in sorted(heights.items())]))