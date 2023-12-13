P = complex

def isHorizFlip(grid, maxX, x, part2):
	flag = False
	for p in grid:
		newP = P(x + (x+1 - p.real) , p.imag)
		if 0 <= newP.real <= maxX and newP not in grid:
			if not part2 or flag:
				return False
			flag = True
	return not part2 or flag

def isVertFlip(grid, maxY, y, part2):
	flag = False
	for p in grid:
		newP = P(p.real, y + (y+1 - p.imag))
		if 0 <= newP.imag <= maxY and newP not in grid:
			if not part2 or flag:
				return False
			flag = True
	return not part2 or flag

def solve(grid, maxX, maxY, part2 = False):
	for x in range(maxX):
		if isHorizFlip(grid, maxX, x, part2):
			return x + 1
	for y in range(maxY):
		if isVertFlip(grid, maxY, y, part2):
			return 100*(y + 1)


def parse(raw):
	maxY = len(raw.splitlines())-1
	maxX = len(raw.splitlines()[0])-1
	grid = set()
	for y, l in enumerate(raw.splitlines()):
		for x, v in enumerate(l):
			if v == '#':
				grid.add(P(x,y))
	return grid, maxX, maxY

def main(input):
	grids = [parse(raw) for raw in input.split('\n\n')]
	return sum(solve(*g) for g in grids), sum(solve(*g, True) for g in grids)