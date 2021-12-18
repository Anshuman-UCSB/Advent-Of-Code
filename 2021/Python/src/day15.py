from utils.aocUtils import *
from random import random


def main(input:str):
	# g = gridify(input, int)
	g = [list(map(int, l)) for l in input.splitlines()]
	side = len(input.splitlines())
	def access(g, x, y):
		a, am = divmod(x, side)
		b, bm = divmod(y, side)
		return (g[bm][am]+a+b-1)%9+1

	end = (side-1, side-1)
	end2 = (side*5-1, side*5-1)
	seen = set()
	queue = [[] for _ in range(20)]
	queue[0].append((0, 0, 0))
	i = 0
	neighbors = [(0,1),(0,-1),(1,0),(-1,0)]
	p1 = None
	while True:
		for p in queue[i]:
			risk, x, y = p
			if (x,y) in seen:
				continue
			seen.add((x,y))
			if (x,y) == end and p1 == None:
				p1 = risk
			if (x,y) == end2:
				return (p1, risk)
			for n in neighbors:
				a, b = x+n[0], y+n[1]
				if a>=0 and b>=0:
					queue[(i+access(g, a,b))%20].append((risk+access(g, a,b), a,b))
		queue[i].clear()
		i = (i+1)%20