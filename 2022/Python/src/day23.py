from collections import Counter
P = complex
unpack = lambda xs: map(int, (xs.real, xs.imag))
def printGrid(grid,highlight=set()):
	lx=ly=float('inf')
	hx=hy=float('-inf')
	for x,y in map(unpack, grid):
		lx = min(lx, x)
		ly = min(ly, y)
		hx = max(hx, x)
		hy = max(hy, y)
	print()
	for y in range(hy,ly-1,-1):
		for x in range(lx,hx+1):
			if P(x,y) in highlight:
				print('@',end='')
			else:
				print('#' if P(x,y) in grid else '.',end='')
		print()

dirs = {'N': 1j, 'NE': (1+1j), 'NW': (-1+1j), 'S': -1j, 'SE': (1-1j), 'SW': (-1-1j), 'E': 1, 'W': -1}
def getProposal(grid, elfPos, turn):
	for dx in dirs.values():
		if elfPos+dx in grid:
			break
	else:
		return elfPos # no neighbors
	rules = [
		(('NW','N','NE'),'N'),
		(('SW','S','SE'),'S'),
		(('SW','W','NW'),'W'),
		(('SE','E','NE'),'E'),
	]
	for check, prop in rules[turn:]+rules[:turn]:
		if all(elfPos+dirs[d] not in grid for d in check):
			return elfPos+dirs[prop]
	return elfPos

def iter(grid, turn):
	proposals = {}
	c = Counter()
	for elf in grid:
		prop = getProposal(grid,elf,turn)
		proposals[elf] = prop
		c[prop]+=1
	n_grid = set()
	for elf in grid:
		prop = proposals[elf]
		n_grid.add(prop if c[prop]==1 else elf)
	return n_grid

def p1Score(grid):
	lx=ly=float('inf')
	hx=hy=float('-inf')
	for x,y in map(unpack, grid):
		lx = min(lx, x)
		ly = min(ly, y)
		hx = max(hx, x)
		hy = max(hy, y)
	return (hy-ly+1)*(hx-lx+1)-len(grid)

def main(input:str):
	p1 = p2 = 0
	grid = set()
	for y, row in enumerate(input.splitlines()):
		for x, v in enumerate(row):
			if v == '#':
				grid.add(P(x,-y))
	for turn in range(10):
		grid = iter(grid,turn%4)
	for turn in range(10,99999):
		old = grid
		grid = iter(grid,turn%4)
		if old == grid:
			p2 = turn+1
			break
	return (p1Score(grid), p2)