from utils.aocUtils import *
from utils.grid import *
from src.intcode import *

dirMap = {
	1:2,
	2:1,
	3:4,
	4:3
}

def checkDir(c, pos, m, dir):
	dx = [None,1j,-1j,-1,1]
	c.push(dir)
	c.run(True)
	o = c.pop()
	if o != 0:
		c.push(dirMap[dir])
		c.run(True)
		c.pop()
	m[dx[dir]+pos]=o
	return o != 0
	
def exploreSides(c, pos, m):
	validSides = []
	for i in range(4):
		if checkDir(c, pos, m, i+1):
			validSides.append(i+1)
	return validSides

def explore(input):
	pos = 0
	c = CPU(input)
	charmap = {None:" ",0:"#",1:'.',2:"O"}
	m = {pos:1}
	q = []
	dirMod = {1:1j, 2:-1j, 3:-1, 4:1}
	seen = set()
	bt = True
	while True:
		valids = exploreSides(c, pos, m)
		bt = True
		for v in valids:
			if pos+dirMod[v] not in seen:
				c.push(v)
				q.append(v)
				c.run(True)
				c.pop()
				pos+=dirMod[v]
				seen.add(pos)
				bt = False
				break
		if bt == True:
			dir = dirMap[q.pop(-1)]
			c.push(dir)
			c.run(True)
			c.pop()
			pos+=dirMod[dir]
		if q == []: break
		# printInfiniteMapIm(m, charmap, (pos, 'D'))
		
	return m

class p1Grid(GridType):
	def __init__(self, m):
		self.m = m.copy()

	def at(self, crd):
		return self.m[crd] == 0
	def getNeighbors(self, crd):
		return [crd+1, crd-1, crd+1j, crd-1j]
	
def p1s(m):
	g = p1Grid(m)
	for p, v in m.items():
		if v == 2:
			return g.bfs(0, p)[0]

def p2s(m):
	g = p1Grid(m)
	for p, v in m.items():
		if v == 2:
			target = g.getReachable(p, 1000)
			for i in range(1000):
				if g.getReachable(p, i)==target:
					return i

def main(input:str):
	charmap = {None:" ",0:"#",1:'.',2:"O"}
	m = explore(input)
	# printInfiniteMapIm(m, charmap)
	p1 = p1s(m)
	p2 = p2s(m)
	return (p1, p2)