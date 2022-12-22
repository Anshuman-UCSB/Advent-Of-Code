import re

P = complex

def printGrid(grid, pos=None):
	hx=hy=0
	for xy in grid.keys():
		x,y = int(xy.real), int(xy.imag)
		hx = max(hx, x)
		hy = max(hy, y)
	for y in range(hy+1):
		for x in range(hx+1):
			if P(x,y) == pos:
				print('@',end='')
			elif P(x,y) in grid:
				print(grid[P(x,y)],end='')
			else:
				print(' ',end='')
		print()

def getSquare(grid, pos, dir):
	if grid.get(pos+dir, ' ') == '.':
		return pos+dir
	elif grid.get(pos+dir, ' ') == '#':
		return pos
	elif pos+dir not in grid:
		t = pos
		while t in grid:
			t -= dir
		t += dir
		return pos if grid.get(t, ' ') == '#' else t
	else:
		assert False

neighbors = {
	0:[5, 1, 2, 3],
	# 1:[]
} # TODO: need paper for this
def p2Translation(sideNo, pos, dir):
	ind = [-1j, 1, 1j, -1].index(dir)
	

def main(input:str):
	p1 = p2 = 0
	raw, instr = input.split('\n\n')
	grid = {}
	for y, row in enumerate(raw.splitlines()):
		for x, v in enumerate(row):
			if v != ' ':
				grid[P(x+1,y+1)] = v
	instr = re.findall(r'(\d+|\w)',instr)
	# printGrid(grid)
	dir = 1
	pos = 1j
	while pos not in grid:
		pos += 1
	for i in instr:
		if i == 'R':
			dir *= 1j
		elif i == 'L':
			dir *= -1j
		else:
			for _ in range(int(i)):
				n = getSquare(grid, pos, dir)
				if n == pos:
					break
				pos = n
				# printGrid(grid, pos)
	col, row = pos.real, pos.imag
	dirScore= [1,1j,-1,-1j]
	p1 = int(1000*row+4*col+dirScore.index(dir))
	
	sideLen = 50
	offsets = [(1,0),(2,0),(1,1),(0,2),(1,2),(0,3)]
	sides = []
	for dx, dy in offsets:
		sides.append({})
		for y in range(sideLen):
			for x in range(sideLen):
				sides[-1][P(x,y)] = grid[P(dx*sideLen+1+x,dy*sideLen+1+y)]
	# printGrid(sides[2])	
	return (p1, p2)