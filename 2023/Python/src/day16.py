from collections import defaultdict
P = complex

def getStraights(d):
	out = '.'
	if d.real == 0:
		out+="|"
	elif d.imag == 0:
		out+="-"
	return out
def getCW(d):
	out = ''
	if d.real == 0:
		out+='-/'
	elif d.imag == 0:
		out+='|\\'
	return out
def getCCW(d):
	out = ''
	if d.real == 0:
		out+='-\\'
	elif d.imag == 0:
		out+='|/'
	return out

def score(grid, entry, d):
	seen = defaultdict(list)
	beams = [(entry, d)]
	while beams:
		newBeams = []
		for p,d in beams:
			if p not in grid or d in seen[p]:
				continue
			seen[p].append(d)

			if grid[p] in getStraights(d):
				newBeams.append((p+d,d))
			if grid[p] in getCW(d):
				nd = d * 1j
				newBeams.append((p+nd,nd))
			if grid[p] in getCCW(d):
				nd = d * -1j
				newBeams.append((p+nd,nd))
		beams = newBeams
	return len(seen)

def main(input):
	grid = {}
	shape = len(input.splitlines())
	for y,r in enumerate(input.splitlines()):
		for x,v in enumerate(r):
			grid[P(x,y)] = v
	p2 = 0
	for i in range(shape):
		p2 = max(p2, 
			score(grid, P(i,0), 1j),
			score(grid, P(i,shape-1), -1j),
			score(grid, P(0,i), 1),
			score(grid, P(shape-1,i), -1)
			)
	return score(grid, 0, 1), p2