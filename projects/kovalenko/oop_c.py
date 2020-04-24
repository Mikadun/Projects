class BaseObject:
    def __init__(self, x, y, z):
        self.xyz = [x, y, z]

    def get_coordinates(self):
        return self.xyz

class Block(BaseObject):
    def shatter(self):
        self.xyz = [None, None, None]

class Entity(BaseObject):
    def move(self, x, y, z):
        self.xyz = [x, y, z]

class Thing(BaseObject):
    pass

block = Block(1, 2, 3)
ent = Entity(0, -1, -2)
thing = Thing(0, 0, 0)

print(block.get_coordinates())
ent.move(4, 4, 4)
print(ent.get_coordinates())
print(thing.get_coordinates())