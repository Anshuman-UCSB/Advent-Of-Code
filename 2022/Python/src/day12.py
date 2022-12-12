from utils.aocUtils import *
import heapq

class Heap:
	def __init__(self):
		self.q = []
	def push(self,val):
		heapq.heappush(self.q, val)
	def pop(self):
		return heapq.heappop(self.q)
	def size(self):
		return len(self.q)
	def __str__(self):
		return str(self.q)

def main(input:str):
	p1 = p2 = 0
	grid = []
	def validCoord(x, y):
		return 0<=x<len(grid[0]) and 0<=y<len(grid)

	directions = [(0,1), (1,0), (0,-1), (-1, 0)]

	for y,l in enumerate(input.splitlines()):
		grid.append([])
		for x, c in enumerate(l):
			val = None
			if c == 'S':
				val = 0
				start = (x,y)
			elif c == 'E':
				val = 26
				end = (x,y)
			else:
				val = ord(c)-ord('a')
			grid[-1].append(val)
	
	heap = Heap()
	heap.push((0, start[0], start[1]))
	seen = set()
	while True:
		step, x, y = heap.pop()
		if (x,y) in seen:
			continue
		seen.add((x, y))
		if (x,y) == end:
			p1 = step
			break
		for dx, dy in directions:
			nx, ny = x+dx, y+dy
			if (nx,ny) in seen:
				continue
			if validCoord(nx, ny) and grid[ny][nx]-1 <= grid[y][x]:
				heap.push((step+1, nx, ny))
	
	heap = Heap()
	heap.push((0, end[0], end[1]))
	seen = set()
	while True:
		step, x, y = heap.pop()
		if (x,y) in seen:
			continue
		seen.add((x, y))
		if grid[y][x] == 0:
			p2 = step
			break
		for dx, dy in directions:
			nx, ny = x+dx, y+dy
			if (nx,ny) in seen:
				continue
			if validCoord(nx, ny) and grid[y][x]-1 <= grid[ny][nx]:
				heap.push((step+1, nx, ny))

	return (p1, p2)