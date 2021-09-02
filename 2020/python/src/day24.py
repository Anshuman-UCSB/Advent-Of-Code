from utils.aocUtils import *
from utils.gol import GameOfLife

hexDists = {
	"e":2,
	"se":1-1j,
	"sw":-1-1j,
	"w":-2,
	"nw":-1+1j,
	"ne":1+1j
}

class gol24(GameOfLife):
	def __init__(self, blackTiles):
		self.state = blackTiles
	
	def logic(self, alive, count):
		if alive:
			return count == 1 or count==2
		else:
			return count == 2
	
	def getNeighbors(self, coord):
		out = []
		for dx in list(hexDists.values()):
			t = coord+dx
			if self.inBound(t):
				out.append(t)
		return out

def main(input:str):
	blackTiles = set()
	for l in input.splitlines():
		pos = 0
		build = ""
		for c in l:
			build+=c
			if build not in ['s', 'n']:
				pos+=hexDists[build]
				build = ""
		if pos in blackTiles:
			blackTiles.discard(pos)
		else:
			blackTiles.add(pos)
	g = gol24(blackTiles)
	for i in range(100):
		g.iter()
		# print(i,":",g.score())
	p1 = len(blackTiles)
	p2 = g.score()
	return (p1, p2)