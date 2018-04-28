fin = open('compressed.txt', 'r').read()

def string_split(string):
  #
  string += '0'
  last_digit = True
  result = []
  count = ''
  s = ''
  for c in string:
    if str.isdigit(c) and last_digit:
      count += c
    elif str.isdigit(c):
      result.append([int(count), s])
      count = c
      s = ''
      last_digit = True
    else:
      s += c
      last_digit = False
  return result

def decoder(container):
  ctrl_bit = pow(2, 7) - 1
  result = ''
  for i in container:
    count = i[0] & ctrl_bit
    result += i[1] * (count if count != i[0] else 1)
  return result
  
fout = open('decompressed.txt', 'w').write(decoder(string_split(fin)))