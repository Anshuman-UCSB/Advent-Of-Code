from utils.aocUtils import *
from src.intcode import *

def part1(map):
	visited = set()
	target = None
	for p, v in map.items():
		if v == 'O':
			target = p
	dist = -1
	q = [0]
	dirMod = [1, -1, 1j, -1j]
	while target not in visited:
		t = []
		for p in q:
			if p in visited:
				continue
			visited.add(p)
			t.extend([p+d for d in dirMod if map[p+d] != '#'])
		q = t
		dist += 1
	return dist
def part2(map):
	visited = set()
	start = None
	target = list(map.values()).count('.')
	for p, v in map.items():
		if v == 'O':
			start = p
	dist = 0
	q = [start]
	dirMod = [1, -1, 1j, -1j]
	while target > len(visited):
		t = []
		for p in q:
			if p in visited:
				continue
			visited.add(p)
			t.extend([p+d for d in dirMod if map[p+d] != '#'])
		q = t
		dist += 1
	return dist

def main(input:str):
	dirMap = {1:1j, 2:-1j, 3:1, 4:-1}
	opposites = {1:2, 2:1, 3:4, 4:3}
	visited = set()
	c = CPU(input)
	pos = 0
	map = {pos:"."}
	path = []
	def _explore(pos):
		visited.add(pos)
		for i in range(1,5):
			c.push(i)
			c.runUntilInput()
			response = c.pop()
			if response == 0:
				map[pos+dirMap[i]] = '#'
			elif response == 1:
				map[pos+dirMap[i]] = '.'
				pos += dirMap[i]
				if pos not in visited:
					_explore(pos)
				pos -= dirMap[i]
				c.push(opposites[i])
				c.runUntilInput()
				assert(c.pop() != 0)
			elif response == 2:
				map[pos+dirMap[i]] = 'O'
				c.push(opposites[i])
				c.runUntilInput()
				assert(c.pop() != 0)
	_explore(pos)

	p1 = part1(map)
	p2 = part2(map)

	map[0] = 'D'
	
	return (p1, p2)