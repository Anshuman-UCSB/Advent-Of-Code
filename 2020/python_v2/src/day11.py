def getAdj(pos):
	adj = (-1j-1, -1j, -1j+1, -1, 1, 1j-1, 1j, 1j+1)
	return {pos+a for a in adj}
def iter(seats, occ):
	nocc = set()
	for s in seats:
		if (s in occ and len(occ&getAdj(s))<4) or (s not in occ and len(occ&getAdj(s)) == 0):
			nocc.add(s)
	return nocc, nocc != occ
	
def iter2(seats, occ,adj):
	nocc = set()
	for s in seats:
		if (s in occ and len(occ&adj[s])<5) or (s not in occ and len(occ&adj[s]) == 0):
			nocc.add(s)
	return nocc, nocc != occ
	
def main(input):
	xbounds = len(input.splitlines()[0])-1
	ybounds = len(input.splitlines())
	seats = set()
	for y,row in enumerate(input.splitlines()):
		for x, v in enumerate(row):
			if v != '.': seats.add(x+1j*y)
	occ = set()
	changed = True
	while changed:
		occ, changed = iter(seats, occ)
	p1 = len(occ)

	adjMap = {}
	for s in seats:
		adjMap[s] = set()
		for d in (-1j-1, -1j, -1j+1, -1, 1, 1j-1, 1j, 1j+1):
			p = s + d
			while 0<=p.real<=xbounds and 0<=p.imag<=ybounds:
				if p in seats:
					adjMap[s].add(p)
					break
				p+=d
	occ = set()
	changed = True
	while changed:
		occ, changed = iter2(seats, occ, adjMap)
	return p1, len(occ)