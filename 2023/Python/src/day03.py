P = complex
adj = [P(-1,1), P(0,1),  P(1,1),
		P(-1,0), 		 P(1,0),
		P(-1,-1), P(0,-1), P(1,-1)]

def getNum(grid, pos):
	if pos not in grid or not grid[pos].isnumeric():
		return None
	# pos is in grid, and is a digit
	while pos-1 in grid and grid[pos-1].isnumeric():
		pos -= 1
	start = pos
	num = ""
	while pos in grid and grid[pos].isnumeric():
		num+=grid[pos]
		pos+=1
	return start, int(num)

def getAdjParts(grid, pos):
	parts = set()
	for d in adj:
		parts.add(getNum(grid, pos+d))
	return parts-{None}

def p1(grid, symbols):
	parts = set()
	for s in symbols:
		parts|=getAdjParts(grid, s)
	p1 = 0
	for p in parts:
		p1+=p[1]
	return p1

def p2(grid, symbols):
	ans = 0
	for s in symbols:
		if grid[s] != '*': continue
		parts = list(getAdjParts(grid, s))
		if len(parts) == 2:
			ans += parts[0][1]*parts[1][1]
	return ans

def main(input):
	grid = {}
	symbols = []
	for y, line in enumerate(input.splitlines()):
		for x, v in enumerate(line):
			if v != ".":
				grid[P(x,y)] = v
				if not v.isnumeric():
					symbols.append(P(x,y))
	return p1(grid, symbols), p2(grid, symbols)