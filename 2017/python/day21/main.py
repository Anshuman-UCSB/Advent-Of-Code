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
	return v
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
			new[j+y][i+x]=copy[j][i]
def blank(size):
	return [[None]*size for _ in range(size)]

def iter(g,rules):
	if len(g)%2==0:
		new = blank(len(g)//2*3)
		print(new)
	elif len(g)%3==0:
		new = blank(len(g)//3*4)
		for y in range(len(g)//3):
			for x in range(len(g)//3):
				# TODO: slice grid
				# copyTo(new, rules[toNum()])
		print(new)
	
def day21(input):
	grid = toGrid(".#./..#/###")
	rules = {}
	for l in input.splitlines():
		lhs,rhs = l.split(" => ")
		lhs,rhs=toGrid(lhs),toGrid(rhs)
		for _ in range(2):
			for _ in range(4):
				rules[toNum(lhs)]=rhs
				printGrid(lhs)
				lhs = rotate(lhs)
			lhs=flip(lhs)
	iter(grid,rules)
	return [None,None]