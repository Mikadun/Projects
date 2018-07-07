#!/usr/bin/python
# -*- coding: utf-8 -*-
 
import sys
from random import randint
from tkinter import Tk, Frame, Canvas, ALL, NW
 
WIDTH = 400
HEIGHT = 400
DOT_SIZE = 40 
MINES = 20
MINE_VALUE = 100
BOARD_WIDTH = int(WIDTH / DOT_SIZE)
BOARD_HEIGHT = int(HEIGHT / DOT_SIZE)

class Board(Canvas):
 
    def __init__(self, parent):
        Canvas.__init__(self, width=WIDTH, height=HEIGHT, 
            background="grey", highlightthickness=0)
         
        self.parent = parent 
        self.board = [[0] * BOARD_HEIGHT] * BOARD_WIDTH # Be careful with that, when w and h ll different
        self.initGame()
        self.pack()
                       
    def onClick(*args): 
        x = int(args[1].x / DOT_SIZE) * DOT_SIZE
        y = int(args[1].y / DOT_SIZE) * DOT_SIZE
        args[1].widget.create_rectangle(x, y, x + DOT_SIZE, y + DOT_SIZE, fill="white")


    def initGame(self):
        self.focus_get()
        self.createGrid()
        self.createMines()
        for i in self.board:
            print(i)
        self.bind('<1>', self.onClick)        
 
    def createGrid(self):
        for i in range(DOT_SIZE, WIDTH, DOT_SIZE):
            self.create_line(i, 0, i, HEIGHT)

        for i in range(DOT_SIZE, HEIGHT, DOT_SIZE):
            self.create_line(0, i, WIDTH, i)
    
    def createMines(self):
        board = self.board
        mines_left = MINES - 19
        while(mines_left > 0):
            rx = randint(0, BOARD_WIDTH - 1)
            ry = randint(0, BOARD_HEIGHT - 1)
            print('[', rx, ',', ry, ']: ', board[rx][ry])
            if(board[rx][ry] < MINE_VALUE):
                i = rx
                y = ry
                board[i][y] = MINE_VALUE
            mines_left -= 1

    def gameOver(self):
 
        self.delete(ALL)
        self.create_text(self.winfo_width()/2, self.winfo_height()/2, 
            text="Game Over", fill="white")            
 
 
class Nibbles(Frame):
 
    def __init__(self, parent):
        Frame.__init__(self, parent)
                
        parent.title('Nibbles')
        self.board = Board(parent)
        self.pack()
 
 
def main():
 
    root = Tk()
    nib = Nibbles(root)
    root.mainloop()  
 
 
if __name__ == '__main__':
    main()
