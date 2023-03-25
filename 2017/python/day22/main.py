from collections import defaultdict
def day22(input):
	input = input.splitlines()
	y = len(input)
	x = len(input[0])
	pos = x//2 - y//2 * 1j
	grid = set()
	grid2 = defaultdict(int)
	for j,row in enumerate(input):
		for i,v in enumerate(row):
			if v == '#':
				grid.add(i-j*1j)
				grid2[i-j*1j] = 2
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
		
	pos = x//2 - y//2 * 1j
	d = 1j

	infect2 = 0
	dd = [1j, 1, -1j, -1]
	for _ in range(10000000):
	# for _ in range(100):
		d*=dd[grid2[pos]]
		grid2[pos]=(grid2[pos]+1)%4
		if grid2[pos] == 2:
			infect2+=1
		pos+=d
		# print(grid2)

	return [infect,infect2]