from itertools import permutations
def main(input:str) -> tuple:
	dists = {}
	pool = set()
	for l in input.splitlines():
		spl = l.split()
		dists[(spl[0], spl[2])] = int(spl[-1])
		dists[(spl[2], spl[0])] = dists[(spl[0], spl[2])]
		pool.add(spl[0])
		pool.add(spl[2])
	p1, p2 = 999999, 0
	for path in permutations(pool):
		length = 0
		for i in range(0,len(path)-1):
			length+=dists[(path[i], path[i+1])]
		p1 = min(p1, length)
		p2 = max(p2, length)
	return (p1, p2)