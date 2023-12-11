P = complex

def getDist(a,b):
	return int(abs(a.imag - b.imag) + abs(a.real - b.real))

def solve(raw, empty, part1=True):
	factor = 1 if part1 else 1_000_000-1
	grid = []
	for p in raw:
		mod = P(
			sum(a<p.real for a in empty[0]),
			sum(a<p.imag for a in empty[1])
		) * factor
		grid.append(p+mod)
	
	ans = 0
	for i in range(len(grid)-1):
		for j in range(i+1, len(grid)):
			ans += getDist(grid[i], grid[j])
	return ans

def main(input):
	raw = []
	lim = len(input.splitlines())
	empty = [set(range(lim)), set(range(lim))]
	
	for y, l in enumerate(input.splitlines()):
		for x, v in enumerate(l):
			if v == '#':
				raw.append(P(x,y))
				empty[0] -= {x}
				empty[1] -= {y}
	
	return solve(raw, empty, True), solve(raw, empty, False)