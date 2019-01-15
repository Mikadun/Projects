
SIZE = 255

class Vertex:
  def __init__(self, char = '#', idx = 0, parent = 0):
    self.childs = [-1] * SIZE
    self.leaf = False
    self.idx = idx
    self.char = char
    self.parent = parent
    self.link = -1
    self.good_link = -1
    self.move = [-1] * SIZE

    self.s_idx = 0
    self.s_len = 0

class Trie:
  def __init__(self):
    self.vxs = [Vertex()]
    self.s_idx = 0

  def push(self, string):
    v = self.vxs[0]
    for char in string:
      c = ord(char)
      if v.childs[c] != -1:
        v = self.vxs[v.childs[c]]
      else:
        idx = len(self.vxs)
        self.vxs.append(Vertex(char, idx, v.idx))
        v.childs[c] = idx
        v = self.vxs[idx]
    v.leaf = True
    v.s_idx = self.s_idx
    v.s_len = len(string)
    self.s_idx += 1

  def show(self, v = None, string = ''): 
    if v == None:
      v = self.vxs[0]

    print(v.char, v.good_link)
    if v.leaf:
      print(string, v.idx)
    
    for i in range(SIZE):
      if v.childs[i] != -1:
        self.show(self.vxs[v.childs[i]], (string + chr(i)))

  def get_link(self, idx):
    v = self.vxs[idx]
    if v.link == -1:
      if idx == 0 or v.parent == 0:
        v.link = 0
      else:
        v.link = self.get_move(self.get_link(v.parent), v.char)
    return v.link

  def get_move(self, idx, char):
    v = self.vxs[idx]
    c = ord(char)
    if v.move[c] == -1:
      if v.childs[c] != -1:
        v.move[c] = v.childs[c]
      else:
        if idx == 0:
          v.move[c] = 0
        else:
          v.move[c] = self.get_move(self.get_link(idx), char)
    return v.move[c]

  def get_good_link(self, idx):
    v = self.vxs[idx]
    if v.good_link == -1:
      link = self.get_link(idx)
      u = self.vxs[link]
      if link == 0 or u.leaf:
        v.good_link = link
      else:
        v.good_link = self.get_good_link(link)
        
    return v.good_link

  def find(self, idx, pos):
    result = []
    while idx != 0:
      v = self.vxs[idx]
      if v.leaf:
        result.append(tuple([v.s_idx, pos - v.s_len]))
      idx = self.get_good_link(idx)
    return result

  def find_all(self, s):
    v = 0
    result = []
    for i in range(len(s)):
      v = self.get_move(v, s[i])

      for res in self.find(v, i + 1):
        result.append(res)

    result = sorted(result)
    for i in result:
      print('substring', i[0], 'occur in pos', i[1])

trie = Trie()
trie.push('he')
trie.push('she')

trie.find_all('she')
