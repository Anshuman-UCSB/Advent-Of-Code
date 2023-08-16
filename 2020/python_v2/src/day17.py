neighbors = {(x,y,z) for x in range(-1,2) for y in range(-1,2) for z in range(-1,2)} - {(0,0,0)}
neighbors2 = {(x,y,z,w) for x in range(-1,2) for y in range(-1,2) for z in range(-1,2) for w in range(-1,2)} - {(0,0,0,0)}

def add(p1, p2):
	return tuple(sum(z) for z in zip(p1,p2))
def getNeighbors(p):
	return {add(p, d) for d in neighbors}
def getNeighbors2(p):
	return {add(p, d) for d in neighbors2}

def iter(grid):
	consider = set()
	for p in grid:
		consider.add(p)
		consider|=getNeighbors(p)
	new_grid = set()
	for p in consider:
		if (len(getNeighbors(p)&grid) == 3) or ((p in grid) and (len(getNeighbors(p)&grid) == 2)):
			new_grid.add(p)
	return new_grid
def iter2(grid):
	consider = set()
	for p in grid:
		consider.add(p)
		consider|=getNeighbors2(p)
	new_grid = set()
	for p in consider:
		if (len(getNeighbors2(p)&grid) == 3) or ((p in grid) and (len(getNeighbors2(p)&grid) == 2)):
			new_grid.add(p)
	return new_grid
def main(input):
	grid1 = set()
	grid2 = set()
	for y, row in enumerate(input.splitlines()):
		for x,v in enumerate(row):
			if v == '#':
				grid1.add((x,y,0))
				grid2.add((x,y,0,0))
	for _ in range(6):
		grid1 = iter(grid1)
		grid2 = iter2(grid2)
	return len(grid1), len(grid2)