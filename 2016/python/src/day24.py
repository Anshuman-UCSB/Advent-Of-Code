from src.grid import GridType
from itertools import permutations
import numpy as np

class Maze(GridType):
	def __init__(self, inp):
		self.grid = []
		self.pos = {}
		for l in inp.splitlines():
			self.grid.append([x for x in l])
		self.grid = np.array(self.grid)
		needle = 0
		try:
			while True:
				y, x = np.argwhere(self.grid == str(needle))[0]
				self.pos[needle] = (x,y)
				needle+=1
		except:
			# print(self.pos)
			pass

	def at(self, crd) -> bool: #return true if wall
		return self.grid[crd[1],crd[0]] == '#'
		
	def print(self):
		for r in self.grid:
			print("".join(r))

def main(input:str) -> tuple:
	m = Maze(input)
	# m.print()
	dists = {}
	for a, p1 in m.pos.items():
		for b, p2 in m.pos.items():
			if (a,b) not in dists:
				if (b,a) in dists:
					dists[(a,b)] = dists[(b,a)]
				else:
					dists[(a,b)] = m.bfs(p1, p2)[0]
	pool = [x for x in m.pos.keys()]
	pool.remove(0)
	p1 = 9999999
	p2 = 9999999
	for path in permutations(pool):
		length = dists[(0,path[0])]
		for i in range(0,len(path)-1):
			length += dists[(path[i], path[i+1])]
		p1 = min(length, p1)
		p2 = min(p2,length + dists[(path[-1], 0)])

	
	# print(dists)
	return (p1, p2)
