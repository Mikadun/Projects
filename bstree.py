class Node:
  
  def __init__( self, key ):
    self.key = key
    self.left = None
    self.right = None

  def insert( self, key ):

    if key == self.key:
      return

    if key > self.key:
      if self.right != None:
        self.right.insert( key )
      else:
        self.right = Node( key )
    else:
      if self.left != None:
        self.left.insert( key )
      else:
        self.left = Node( key )

  def print( self ):
    if self.left != None:
      self.left.print()
    
    print( self.key, end=' ' )

    if self.right != None:
      self.right.print()


class Tree:
  
  root = None
  
  def insert( self, key ):
    if self.root == None:
      self.root = Node( key )
    else:
      self.root.insert( key )
    
  def print( self ):
    if self.root != None:
      self.root.print()


tree = Tree()

for i in range(10):
  tree.insert( i )

tree.print()
