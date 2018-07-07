
from PIL import Image, ImageDraw
from time import clock

start_time = clock()

# Loading filter colors
filter_img = Image.open("filter.png")
f_size = filter_img.size
filter_img = filter_img.load()
filter_colors = []
for i in range(f_size[0]):
  for j in range(f_size[1]):
    filter_colors.append(filter_img[i, j])

# Loading main image
image = Image.open("image.png")
draw = ImageDraw.Draw(image)
h, w = image.size

# Start and end points
start = [0, 0]
end = [h - 1, w - 1]


def is_in_filter(x, y):
  px = image.getpixel((x, y))
  for i in filter_colors:
    if i == px:
      return True
  return False

def in_range(v): 
  return v[0] > -1 and v[0] < h and v[1] > -1 and v[1] < w

def distance(v):
  return abs(end[0] - v[0]) + abs(end[1] - v[1])

used = [[False for i in range(w)] for j in range(h)] 
moves = [ [1, 0], [0, 1], [0, -1], [-1, 0]] # d, r, l, u

deck = [start]      # vertex deck
color = (0, 255, 0) # way color
fcolor = (0, 0, 255)

def A_star(v):
  if used[v[0]][v[1]]:
    return False
  used[v[0]][v[1]] = True

  if v == end:
    print("Found")
    draw.point((v[0], v[1]), fcolor)
    return True

  draw.point((v[0], v[1]), color)

  for move in moves:
    nv = [v[0] + move[0], v[1] + move[1]]
    if in_range(nv) and not used[nv[0]][nv[1]] and is_in_filter(nv[0], nv[1]):
      deck.append(nv)

  return False
      
# Main loop
found = False  # is way found

while len(deck) and not found:
  found = A_star(deck.pop(0))

# Saving result
image.save("ans.png", "PNG")
del draw

delta_t = int(clock() - start_time)
print("It took", delta_t // 60, "min", delta_t % 60, "s")