from utils.aocUtils import *
from src.intcode import *

def p1s(input):
	whites = set()
	pos = 0
	dir = 1j
	c = CPU(input)
	visited = set()
	while not c.done:
		visited.add(pos)
		c.push(1 if pos in whites else 0)
		try:
			c.run()
		except EmptyInput:
			pass
		color = c.pop()
		if color == 1:
			whites.add(pos)
		else:
			whites.discard(pos)
		if c.pop() == 0:
			dir*= 1j
		else:
			dir*=-1j
		pos+=dir

	return len(visited)

def p2s(input):
	c = CPU(input)
	whites = {0}
	pos = 0
	dir = 1j
	c = CPU(input)
	visited = set()
	while not c.done:
		visited.add(pos)
		c.push(1 if pos in whites else 0)
		try:
			c.run()
		except EmptyInput:
			pass
		color = c.pop()
		if color == 1:
			whites.add(pos)
		else:
			whites.discard(pos)
		if c.pop() == 0:
			dir*= 1j
		else:
			dir*=-1j
		pos+=dir
	build = ""
	for y in range(0, -6, -1):
		build += "\n"
		for x in range(0, 41):
			if (x+y*1j) in whites:
				build+='#'
			else:
				build+=" "
	return build 
	

def main(input:str):
	p1 = p1s(input)
	p2 = p2s(input)
	return (p1, p2)