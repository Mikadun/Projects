n = int(input())
points = []
p = sorted([sorted([int(j) for j in input().split()]) for _ in range(n)])
for i in range(n):
  points.append({'l': p[i][0], 'r': p[i][1], 'idx': i + 1})

result = set()
for i in range(n - 1):
  for j in range(i + 1, n):
    if points[i]['l'] <= points[j]['l'] <= points[i]['r']:
      result.add(tuple(sorted([points[i]['idx'], points[j]['idx']])))

if len(result):
  for i in result:
    print(i)
else:
  print("There isn't any intersections")
