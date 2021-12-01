from utils.aocUtils import *
from src.intcode import *
def p1(input):
	c = CPU(input)
	dir = 1j
	pos = 0
	whiteSquares = set()
	visited = set()
	while not c.done:
		c.push(1 if pos in whiteSquares else 0)
		c.runUntilInput()
		shouldPaint = c.pop()
		visited.add(pos)
		if shouldPaint:
			whiteSquares.add(pos)
		else:
			whiteSquares.remove(pos)
		turn = c.pop()
		if turn:
			dir *= -1j
		else:
			dir *= 1j
		pos += dir
	
	return len(visited)
def p2(input):
	c = CPU(input)
	dir = 1j
	pos = 0
	whiteSquares = set([0])
	while not c.done:
		c.push(1 if pos in whiteSquares else 0)
		c.runUntilInput()
		shouldPaint = c.pop()
		if shouldPaint:
			whiteSquares.add(pos)
		else:
			whiteSquares.discard(pos)
		turn = c.pop()
		if turn:
			dir *= -1j
		else:
			dir *= 1j
		pos += dir
	
	return "\n".join([x[::-1] for x in printSet(whiteSquares)[::-1].splitlines()])

def main(input:str):
	return (p1(input), p2(input))