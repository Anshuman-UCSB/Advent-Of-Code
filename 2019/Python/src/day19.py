from utils.aocUtils import *
from src.intcode import *

def testSquare(input, x, y):
	c = CPU(input)
	c.push(x)	
	c.push(y)
	c.run(True)
	return c.pop()

def canFitAtY(input, y, get_x = False):
	x = 0
	while testSquare(input, x,y+99) == 0:
		x+=1
	return not not testSquare(input, x+99, y) if get_x == False else x

def main(input:str):
	p1 = 0
	for y in range(50):
		for x in range(50):
			p1+=testSquare(input, x, y)
	h = 100
	while not canFitAtY(input, h):
		h<<=1
	l=h>>1
	while l<h:
		m = (l+h)>>1
		if canFitAtY(input, m):
			h = m
		else:
			l = m+1
	
	p2 = l+10000*canFitAtY(input, l,True)
	return (p1, p2)