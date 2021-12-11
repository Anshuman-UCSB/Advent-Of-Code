from utils.aocUtils import *

def getNeighbors(p):
	neighbors = [1,-1, 1+1j, 1j, -1+1j, 1-1j, -1j, -1-1j]
	return [p+n for n in neighbors]

def update(g):
	for p in g:
		g[p]+=1
	loop = True
	while loop:
		loop = False
		for c in [p for p in g if g[p] > 9]:
			loop = True
			g[c] = 0
			for n in getNeighbors(c):
				if n in g and g[n] != 0:
					g[n]+=1
	for p in g:
		if g[p]>9:
			g[p] = 0
	return sum(1 for p in g if g[p] == 0)

def main(input:str):
	p1 = 0
	g = gridify(input, int)
	for t in range(100):
		p1+=update(g)
	t = 101
	while update(g) != 100:
		t+=1
	return (p1, t)