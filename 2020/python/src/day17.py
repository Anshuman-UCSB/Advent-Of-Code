from utils.aocUtils import *
from utils.gol import GameOfLife

class gol17(GameOfLife):
	def __init__(self, input, alive = '#'):
		self.state = set()
		spl = input.splitlines()
		for y, r in enumerate(spl):
			for x, v in enumerate(r):
				if v == alive:
					self.state.add((x,y,0))
		# print(self.state)
	def getNeighbors(self, coord):
		out = []
		for dx,dy,dz in [(x,y,z) for x in range(-1,2,1) for y in range(-1,2,1) for z in range(-1,2,1) if (x,y,z) != (0,0,0)]:
			t = (coord[0]+dx, coord[1]+dy, coord[2]+dz)
			if self.inBound(t):
				out.append(t)
		return out
	def pGrid(self):
		for z in range(-3, 3):
			print(z,":")
			for y in range(-2,5):
				for x in range(-2,5):
					print('#' if (x,y,z) in self.state else '.', end="")
				print()

class gol17_2(GameOfLife):
	def __init__(self, input, alive = '#'):
		self.state = set()
		spl = input.splitlines()
		for y, r in enumerate(spl):
			for x, v in enumerate(r):
				if v == alive:
					self.state.add((x,y,0,0))
		# print(self.state)
	def getNeighbors(self, coord):
		out = []
		for dx,dy,dz,dw in [(x,y,z,w) for x in range(-1,2,1) for y in range(-1,2,1) for z in range(-1,2,1) for w in range(-1,2,1) if (x,y,z,w) != (0,0,0,0)]:
			t = (coord[0]+dx, coord[1]+dy, coord[2]+dz, coord[3]+dw)
			if self.inBound(t):
				out.append(t)
		return out

def main(input:str):
	g = gol17(input)
	g2= gol17_2(input)
	for _ in range(6):
		g.iter()
		g2.iter()
	# print(g.state)
	p1 = g.score()
	p2 = g2.score()
	return (p1, p2)