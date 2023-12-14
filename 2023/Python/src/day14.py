def spin(grid):
	for y in range(len(grid)):
		for x in range(len(grid[0])):
			if grid[y][x] == 'O':
				ny = y
				grid[ny][x] = '.'
				while ny >= 0 and grid[ny][x] == '.':
					ny-=1
				grid[ny+1][x] = 'O'
	return list(map(list,zip(*grid[::-1])))

def cycle(grid):
	for i in range(4):
		grid = spin(grid)
	return grid

def score(grid):
	ans = 0
	for y in range(len(grid)):
		for x in range(len(grid[0])):
			if grid[y][x] == 'O':
				ans += len(grid) - y
	return ans
	

def main(input):
	grid = [list(l) for l in input.splitlines()]
	# print(*grid, sep='\n')
	spin(grid)
	p1 = score(grid)
	
	seen = {}
	ff = False

	t = 0
	target = 1000000000
	while t < target:
		grid = cycle(grid)
		t += 1
		h = str(grid)
		
		if not ff and h in seen:
			period = t - seen[h]
			t += ((target-t)//period)*period
			ff = True

		seen[h] = t
	return p1, score(grid)