from utils.aocUtils import *
from utils.gol import GameOfLife

class gol11(GameOfLife):
	def __init__(self, input, valid = 'L'):
		self.valids = set()
		self.state = set()
		spl = input.splitlines()
		for y, r in enumerate(spl):
			for x, v in enumerate(r):
				if v == valid:
					self.valids.add((x,y))
		# print(self.state)
	def iter(self):
		nState = set()
		for c in self.valids:
			# print(self.state)
			nCount = sum([1 for x in self.getNeighbors(c) if x in self.state])
			# print(c, nCount)
			
			if self.logic(c in self.state, nCount):
				nState.add(c)
		self.state = nState
	def inBound(self, coord):
		return coord in self.valids

	def logic(self, alive, count):
		if alive:
			return count < 4
		else:
			return count == 0
class gol11_2(gol11):
	def logic(self, alive, count):
		if alive:
			return count < 5
		else:
			return count == 0
	def getNeighbors(self, coord):
		out = []
		for dx,dy in [(0,1),(0,-1),
					  (1,0),(1,1),(1,-1),
					  (-1,0),(-1,1),(-1,-1)]:
			t = (coord[0]+dx, coord[1]+dy)
			c = 0
			while t not in self.valids:
				t = (t[0]+dx, t[1]+dy)
				c+=1
				if c > 20:
					break
			if self.inBound(t):
				out.append(t)
		return out
		
def pGrid(g):
	for i in range(10):
		for j in range(10):
			if (j,i) in g.valids:
				if (j,i) in g.state:
					print("#",end="")
				else:
					print("L",end="")
			else:
				print(".",end="")
		print()

def main(input:str):
	g = gol11(input)
	old = None
	while old != g.state:
		old = g.state
		g.iter()
	p1 = g.score()
	g_2 = gol11_2(input)
	old = None
	while old != g_2.state:
		# print()
		# pGrid(g_2)
		old = g_2.state
		g_2.iter()
	p2 = g_2.score()
	return (p1, p2)