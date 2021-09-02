from utils.aocUtils import *
from collections import defaultdict, Counter
from operator import mul
import numpy as np

GRIDLEN = 12

class Tile:
	def __init__(self, id, state, grid):
		self.id = id
		self.state = state
		self.grid = np.copy(grid)
		self.edges = [
			"".join(self.grid[0]),
			"".join(self.grid[:,-1]),
			"".join(self.grid[-1]),
			"".join(self.grid[:,0]),
		]
		# print(self.edges)
	
	def p(self):
		print(self.id,'-',self.state)
		for r in self.grid:
			print("".join(r))
	
def p2s(tiles, startId):
	grid = [None]*pow(GRIDLEN,2)
	usedIds = [startId]
	for t in tiles:
		if t.id == startId and t.state == 4:
			grid[0] = t
			break
	return recursiveSolve(tiles, grid, usedIds, 1)

def recursiveSolve(tiles, grid, used, pos):
	# print(grid)
	# for g in grid:
	# 	if g:
	# 		g.p()
	if grid[-1] != None:
		return grid
	possibles = []
	for t in tiles:
		if t.id in used:
			continue
		if pos%GRIDLEN == 0 or grid[pos-1].edges[1] == t.edges[3]:
			if pos<GRIDLEN or grid[pos-GRIDLEN].edges[2] == t.edges[0]:
				possibles.append(t)
	for p in possibles:
		t = grid.copy()
		t[pos] = p
		tused = used.copy()
		tused.append(p.id)
		resp = recursiveSolve(tiles, t, tused, pos+1)
		if resp != None:
			return resp

def matchesMonster(portion):
	jig = [
		"                  # ",
		"#    ##    ##    ###",
		" #  #  #  #  #  #   "
	]
	for y in range(3):
		for x in range(20):
			if jig[y][x] == '#' and portion[y][x] != '#':
				return False
	return True
def countMonsters(grid):
	monsters = 0
	for y in range(len(grid)-2):
		for x in range(len(grid)-20):
			if matchesMonster(grid[y:y+3,x:x+20]):
				monsters+=1
	return monsters

def flips(grid):
	for _ in range(2):
		for i in range(4):
			yield grid
			grid = np.rot90(grid)
		grid = np.flipud(grid)

def main(input:str):
	tiles = []

	edgeCount = defaultdict(set)
	for c in input.split("\n\n"):
		lines = c.splitlines()
		id = int(lines[0][4:-1])
		grid = []
		for l in lines[1:]:
			grid.append(list(l))
		grid = np.array(grid)
		for i in range(2):
			for state in range(4):
				tiles.append(Tile(id, i*4+state, grid))
				for e in tiles[-1].edges:
					edgeCount[e].add(tiles[-1].id)
				# tiles[-1].p()
				grid = np.rot90(grid)
			grid = grid[::-1]
	# print(edgeCount)
	c = Counter([c for x,v in edgeCount.items() if len(v)==2 for c in v ])
	corners = [x[0] for x in c.most_common()[:-5:-1]]
	p1 = reduce(mul, corners)
	p2 = 0
	
	grid = p2s(tiles, corners[0])
	# grid = p2s(tiles, 1951)
	RGRIDLEN = 8
	totalGrid = np.empty((GRIDLEN*RGRIDLEN,GRIDLEN*RGRIDLEN), dtype = str)
	for i, g in enumerate(grid):
		x = i%GRIDLEN
		y = i//GRIDLEN
		# print(g.grid)
		totalGrid[y*RGRIDLEN:(y+1)*RGRIDLEN, x*RGRIDLEN:(x+1)*RGRIDLEN, ] = g.grid[1:-1,1:-1]
	
	# for r in totalGrid:
	# 	print("".join(r))
	for g in flips(totalGrid):
		monsters = countMonsters(g)
		if monsters > 0:
			break
	p2 = (len(totalGrid[totalGrid=='#']))-(15*monsters)

	return (p1, p2)