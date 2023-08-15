def testslope(grid,dx, dy):
	x = y = 0
	hits = 0
	while y < len(grid):
		hits += grid[y][x]
		y+=dy
		x = (x+dx)%len(grid[0])
	return hits

def main(input):
	grid = list(map(lambda x: [int(v=='#') for v in x], input.splitlines()))
	p2 = 1
	p2 *= testslope(grid, 1, 1)
	p2 *= testslope(grid, 3, 1)
	p2 *= testslope(grid, 5, 1)
	p2 *= testslope(grid, 7, 1)
	p2 *= testslope(grid, 1, 2)
	return testslope(grid, 3, 1), p2