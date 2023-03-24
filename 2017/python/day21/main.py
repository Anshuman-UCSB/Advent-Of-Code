import numpy as np

def parse(line):
	g = []
	for l in line.split("/"):
		g.append([c=='#' for c in l])
	return np.array(g)

def iter(grid, rules):
	sz = len(grid)
	if sz % 2 == 0:
		

def day21(input):
	# grid = np.array([[0,1,0],[0,0,1],[1,1,1]],dtype=bool)
	grid = parse(".#./..#/###")
	rules = {}
	for l in input.splitlines():
		lhs,rhs = map(parse,l.split(" => "))
		print(lhs)
		for _ in range(2):
			for _ in range(4):
				lhs = np.rot90(lhs)
				rules[np.array2string(lhs)]=rhs
			lhs = np.fliplr(lhs)
	print(rules)
	return [None,None]