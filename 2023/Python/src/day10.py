P = complex

def changeDir(d, pipe):
	if ((pipe == '7' and d == 1) or
		(pipe == 'J' and d == 1j) or
		(pipe == 'L' and d == -1) or
		(pipe == 'F' and d == -1j)
	):
		return d * 1j
	if ((pipe == '7' and d == -1j) or
		(pipe== 'J' and d == 1) or
		(pipe== 'L' and d == 1j) or
		(pipe== 'F' and d == -1)
	): return d * -1j
	if pipe in "|-": return d

def getPath(grid, start, d):
	path = {}
	pos = start
	origDir = d
	while pos in grid:
		path[pos] = grid[pos]
		pos+=d
		if pos not in grid:
			return None

		if pos == start:
			if d == 1j or origDir == -1j:
				path[start] = '|'
			return path
		
		d = changeDir(d, grid[pos])
		if d == None: # invalid turn
			return None

def cleanTrash(grid, start):
	return getPath(grid, start, 1) or getPath(grid, start, -1) or getPath(grid, start, 1j)

def printGrid(grid, w, h,empty=' '):
	for y in range(h):
		for x in range(w):
			print(grid.get(P(x,y), empty),end="")
		print()

def main(input):
	grid = {}
	start = None
	for y,l in enumerate(input.splitlines()):
		for x,v in enumerate(l):
			if v != '.':
				grid[P(x,y)] = v
				if v == 'S':
					start = P(x,y)
	
	grid = cleanTrash(grid, start)

	p2 = 0
	for y in range(len(input.splitlines())):
		inside = False
		for x in range(len(input.splitlines()[0])):
			if P(x,y) in grid:
				if grid[P(x,y)] in "|JL":
					inside = not inside
			else:
				p2 += inside

	return len(grid) // 2, p2