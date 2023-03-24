def day22(input):
	input = input.splitlines()
	y = len(input)
	x = len(input[0])
	pos = x//2 - y//2 * 1j
	grid = set()
	for j,row in enumerate(input):
		for i,v in enumerate(row):
			if v == '#':
				grid.add(i-j*1j)
	d = 1j

	infect = 0
	for _ in range(10000):
		if pos in grid:
			d *= -1j
			grid.remove(pos)
		else:
			d *= 1j
			grid.add(pos)
			infect+=1
		pos+=d
		# print(grid)
		

	return [infect,None]