from utils.aocUtils import *

def iter(g, w, h):
	for c in ['>','v']:
		canMove = []
		for k, v in g.items():
			if v == c:
				x,y = im2tup(k)
				if c == '>':
					x = (x+1)%w
				else:
					y = (y+1)%h
				if g[crd2im(x,y)] == '.':
					canMove.append(k)
		for k in canMove:
			mod = 1 if c == '>' else 1j
			n = k+mod
			if n.real>=w:
				n-=w
			if n.imag>=h:
				n-=h*1j
			g[k] = '.'
			g[n] = c
	return g
def main(input:str):
	p1 = 0
	p2 = 0
	w = len(input.splitlines()[0])
	h = len(input.splitlines())
	g = gridify(input)
	old = None
	while g != old:
		p1+=1
		old = {k:v for k,v in g.items()}
		g = iter(g, w, h)
		# print(printCoords(old))
	return (p1, p2)