fin = open('input.txt', 'r').read() + '#'

def advanced_RLE(source):
  ctrl_bit = pow(2, 7)
  temp = [0, []]
  result = []
  for i in source:
    if i[0] > 1:
      if temp[0] != 0:
        result.append([temp[0], ''.join(temp[1])])
        temp = [0, []]
      result.append([i[0] | ctrl_bit, i[1]])
    else:
      temp[0] += 1
      temp[1].append(i[1])

  if temp[0] != 0:
  	result.append([temp[0], ''.join(temp[1])])
  return result

def RLE(mode):
  result = []
  count = 1
  for i in range(len(fin) - 1):
    if fin[i] == fin[i+1]:
      count += 1
    else:
      result.append([count, fin[i]])
      count = 1
  return (result if mode == 'standart' else advanced_RLE(result))

def ans_to_str(ans, mode, space):
  result = ''
  if mode == 'bin':
    for i in ans:
      result += bin(i[0])[2:].rjust(8, '0') + i[1] + space
  else:
    for i in ans:
      result += str(i[0]) + i[1] + space
  return result

fout = open('compressed.txt', 'w').write(ans_to_str(RLE('advanced'), 'int', ''))
