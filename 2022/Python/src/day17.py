from utils.aocUtils import *
import numpy as np
from itertools import cycle

GRID_HEIGHT = 10000
rocks = [
	np.array([[1,1,1,1]], dtype=bool),
	np.array([[0,1,0],[1,1,1],[0,1,0]], dtype=bool),
	np.array([[1,1,1],[0,0,1],[0,0,1]], dtype=bool),
	np.array([[1],[1],[1],[1]], dtype=bool),
	np.array([[1,1],[1,1]], dtype=bool),
]
def arrToString(arr, highest, extra = 0):
	out = "\n"
	for l in reversed(arr[:highest+extra]):
		out+='|'
		for v in l:
			out+=('#' if v else '.')
		out+='|\n'
	out+=("+-------+")
	return out

class Grid:
	def __init__(self, input):
		self.grid = np.zeros((GRID_HEIGHT,7),dtype=bool)
		self.r_ind = 0
		self.highest = 0
		self.placed = 0
		self.jets = [c=='>' for c in input]
		self.j_ind = 0
	def getJet(self):
		ind = self.j_ind
		self.j_ind = (self.j_ind+1)%len(self.jets)
		return self.jets[ind]
	def collides(self, x, y):
		rock = rocks[self.r_ind]
		h,w = rock.shape
		return (self.grid[y:y+h,x:x+w]&rock).any()
	def place(self, x, y):
		rock = rocks[self.r_ind]
		self.placed += 1
		self.r_ind = (self.r_ind+1)%len(rocks)
		h,w = rock.shape
		self.grid[y:y+h,x:x+w]|=rock
		while self.grid[self.highest].any():
			self.highest+=1
	def iter(self, prints = False):
		rock = rocks[self.r_ind]
		x = 2
		h,w = rock.shape
		y = self.highest+3
		while True:
			if prints:
				self.printCurrent(x,y)
			if self.getJet():
				if x+w < 7 and not self.collides(x+1,y):
					x+=1
			else:
				if x > 0  and not self.collides(x-1,y):
					x-=1
			if not self.collides(x, y-1) and y>0:
				y-=1
			else:
				self.place(x,y)
				return
	def getState(self, top = 10):
		top = self.grid[self.highest-top:self.highest]
		str_hash = ""
		str_hash+=str(self.r_ind)
		str_hash+=str(self.j_ind)
		for r in top:
			for v in r:
				str_hash+="#" if v else "."
		return(str_hash)

	def printCurrent(self,x,y):
		rock = rocks[self.r_ind]
		h,w = rock.shape
		tmp = np.copy(self.grid)
		tmp[y:y+h,x:x+w]|=rock
		print(arrToString(tmp, self.highest, extra = 8))
	def __str__(self):
		return ("\t\tPLACED: "+str(self.placed)+arrToString(self.grid,self.highest)).replace("\n", "\n\t\t")

def main(input:str):
	p1 = p2 = 0

	grid = Grid(input.strip())
	seen = set()
	saw_hash = False
	for i in range(2022):
		grid.iter()
	p1 = grid.highest
	i = 2022
	while i < 1000000000000:
		grid.iter()
		if saw_hash == False:
			if grid.highest > 100 and grid.getState() in seen:
				saw_hash = True
				str_hash = grid.getState()
				height = grid.highest
				placed = grid.placed
		else:
			if grid.getState() == str_hash:
				dh = grid.highest - height
				dp = grid.placed-placed
				times = (1000000000000-i)//dp
				i+=dp*times
				p2+=dh*times
		seen.add(grid.getState())
		i+=1
	p2+=grid.highest
	return (p1, p2) # 3056 too high