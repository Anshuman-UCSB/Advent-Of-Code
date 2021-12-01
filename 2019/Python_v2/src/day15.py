from utils.aocUtils import *
from src.intcode import *


def main(input:str):
	dirMap = {1:1j, 2:-1j, 3:1, 4:-1}
	opposites = {1:2, 2:1, 3:4, 4:3}
	visited = set()
	c = CPU(input)
	pos = 0
	map = {pos:"."}
	
	def _explore():
		visited.add(pos)
		for i in range(1,5):
			c.push(i)
			c.runUntilInput()
			response = c.pop()
			if response == 0:
				map[pos+dirMap[i]] = '#'
			elif response == 1:
				map[pos+dirMap[i]] = '.'
				c.push(opposites[i])
				c.runUntilInput()
				assert(c.pop() != 0)
			elif response == 2:
				map[pos+dirMap[i]] = 'O'
				c.push(opposites[i])
				c.runUntilInput()
				assert(c.pop() != 0)
	_explore()
	print(printCoords(map))
	print(map)
	p1 = 0
	p2 = 0
	return (p1, p2)