import re

P = complex
unpack = lambda x: (int(x.real), int(x.imag))
def printGrid(grid, pos=None):
	hx=hy=0
	for xy in grid.keys():
		x,y = unpack(xy)
		# x,y = int(xy.real), int(xy.imag)
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
	0:[5,1,2,3],
	1:[5,4,2,0],
	2:[0,1,4,3],
	3:[2,4,5,0],
	4:[2,1,5,3],
	5:[3,4,1,0]
}
newdir = {
	0:[1,1,1j,1],
	1:[-1j,-1,-1,-1],
	2:[-1j,-1j,1j,1j],
	3:[1,1,1j,1],
	4:[-1j,-1,-1,-1],
	5:[-1j,-1j,1j,1j]
}

def coordTranslation(xy,dir,ndir):
	x,y = unpack(xy)
	# Same dir
	if (dir,ndir) == (1,1):
		return P(1,y)
	elif (dir,ndir) == (1j,1j):
		return P(x,1)
	elif (dir,ndir) == (-1,-1):
		return P(50,y)
	elif (dir,ndir) == (-1j,-1j):
		return P(x,50)
	
	# up to right
	elif (dir,ndir) == (-1j,1):
		return P(1,x)
	# left to right
	elif (dir,ndir) == (-1,1):
		return P(1,51-y)
	# left to down
	elif (dir,ndir) == (-1,1j):
		return P(y,1)
	# down to left
	elif (dir,ndir) == (1j,-1):
		return P(50,x)
	# right to up
	elif (dir,ndir) == (1,-1j):
		return P(y,50)
	# right to left
	elif (dir,ndir) == (1,-1):
		return P(50,51-y)
	print("NEED TO DEFINE FOR",dir,ndir)
	exit(0)

def p2Translation(side, pos, dir):
	ind = [-1j, 1, 1j, -1].index(dir)
	x,y = unpack(pos+dir)
	if 1<=x<=50 and 1<=y<=50:
		return side, pos+dir, dir
	ns = neighbors[side][ind]
	ndir = newdir[side][ind]
	return ns, coordTranslation(pos,dir,ndir),ndir

def getSquare_p2(sides, side, pos, dir):
	ns, npos, ndir = p2Translation(side,pos,dir)
	if sides[ns][npos] == '#':
		return side,pos,dir
	else:
		return ns,npos,ndir

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
	col, row = unpack(pos)
	dirScore= [1,1j,-1,-1j]
	p1 = int(1000*row+4*col+dirScore.index(dir))
	
	sideLen = 50
	offsets = [(1,0),(2,0),(1,1),(0,2),(1,2),(0,3)]
	sides = []
	for dx, dy in offsets:
		sides.append({})
		for y in range(sideLen):
			for x in range(sideLen):
				sides[-1][P(x+1,y+1)] = grid[P(dx*sideLen+1+x,dy*sideLen+1+y)]
	
	s,pos,dir = 0,P(1,1),1
	for i in instr:
		if i == 'R':
			dir *= 1j
		elif i == 'L':
			dir *= -1j
		else:
			for _ in range(int(i)):
				n = getSquare_p2(sides,s, pos, dir)
				if n[1] == pos:
					break
				s,pos,dir = n
				# printGrid(grid, pos)
	col,row = unpack(pos)
	p2 = int(1000*(row+100)+4*col+dirScore.index(dir))
	return (p1, p2)