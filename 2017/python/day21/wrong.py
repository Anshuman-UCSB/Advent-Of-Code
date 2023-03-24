def toGrid(s):
	l = []
	for line in s.split('/'):
		l.append([1 if c=="#" else 0 for c in line])
	return l
def toNum(g):
	v = 0
	for row in g:
		for i in row:
			v = v<<1 | i
	return v<<1 | 1 if len(g)==2 else 0
	# issue with the following
	"""
	#.
	..
		and
	#..
	...
	...
	"""
def flip(g):
	return [r[::-1] for r in g]
def rotate(g):
	c = []
	for x in range(len(g)):
		c.append([])
		for y in range(len(g)):
			c[-1].append(g[y][-x-1])
	return c
def printGrid(*gs):
	for g in gs:
		print()
		for row in g:
			for v in row:
				print("#" if v else ".",end='')
			print()
def copyTo(new,copy,x,y):
	for j in range(len(copy)):
		for i in range(len(copy)):
			# printGrid(new,copy)
			# print(x,y,i,j)

			new[j+y][i+x]=copy[j][i]
def blank(size):
	return [[None]*size for _ in range(size)]

def slice(g,x,y,size):
	s = blank(size)
	for j in range(size):
		for i in range(size):
			s[j][i] = g[y+j][x+i]
	return s

def iter(g,rules):
	if len(g)%2==0:
		new = blank(len(g)//2*3)
		for y in range(len(g)//2):
			for x in range(len(g)//2):
				slc = slice(g,x*2,y*2,2)
				copyTo(new, rules[toNum(slc)],x*3,y*3)
		return new
	elif len(g)%3==0:
		new = blank(len(g)//3*4)
		for y in range(len(g)//3):
			for x in range(len(g)//3):
				slc = slice(g,x*3,y*3,3)
				copyTo(new, rules[toNum(slc)],x*4,y*4)
		return new
	
def day21(input):
	grid = toGrid(".#./..#/###")
	rules = {}
	for l in input.splitlines():
		lhs,rhs = l.split(" => ")
		lhs,rhs=toGrid(lhs),toGrid(rhs)
		for _ in range(2):
			for _ in range(4):
				rules[toNum(lhs)]=rhs
				lhs = rotate(lhs)
			lhs=flip(lhs)
	for _ in range(5):
		grid=iter(grid,rules)
	p1 = 0
	for row in grid:
		p1+=sum(row)
	return [p1,None]