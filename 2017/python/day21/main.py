import numpy as np

def parse(line):
	g = []
	for l in line.split("/"):
		g.append([c=='#' for c in l])
	return np.array(g)

def iter(grid, rules):
	sz = len(grid)
	if sz % 2 == 0:
		ngrid = np.ones((sz//2*3,sz//2*3),dtype=bool)
		for y in range(sz//2):
			for x in range(sz//2):
				slc = grid[(y)*2:(y+1)*2,(x)*2:(x+1)*2]
				ngrid[(y)*3:(y+1)*3,(x)*3:(x+1)*3]=rules[np.array2string(slc)]
		return ngrid
	else:
		ngrid = np.ones((sz//3*4,sz//3*4),dtype=bool)
		for y in range(sz//3):
			for x in range(sz//3):
				slc = grid[(y)*3:(y+1)*3,(x)*3:(x+1)*3]
				ngrid[(y)*4:(y+1)*4,(x)*4:(x+1)*4]=rules[np.array2string(slc)]
		return ngrid

def day21(input):
	# grid = np.array([[0,1,0],[0,0,1],[1,1,1]],dtype=bool)
	grid = parse(".#./..#/###")
	rules = {}
	for l in input.splitlines():
		lhs,rhs = map(parse,l.split(" => "))
		for _ in range(2):
			for _ in range(4):
				lhs = np.rot90(lhs)
				rules[np.array2string(lhs)]=rhs
			lhs = np.fliplr(lhs)
	for _ in range(5):
		grid = iter(grid,rules)
	p1 = np.sum(grid)
	for _ in range(18-5):
		grid = iter(grid,rules)
	p2 = np.sum(grid)
	return [p1,p2]