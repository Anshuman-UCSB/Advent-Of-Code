from utils.aocUtils import *
from random import random
from utils.heap import Heap
def main(input:str):
	g = gridify(input, int)
	g2 = {}
	side = len(input.splitlines())
	for y in range(5):
		for x in range(5):
			for p, v in g.items():
				i, j = im2tup(p)
				n = crd2im(i+x*side, j+y*side)
				nv = (v+x+y)
				while nv>=10:
					nv-=9
				g2[n] = nv
	end = crd2im(side-1, side-1)
	end2 = crd2im(side*5-1, side*5-1)

	return (dijkstras(g,0, end, lambda x: g[x])[1], dijkstras(g2,0, end2, lambda x: g2[x])[1])