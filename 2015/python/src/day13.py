from itertools import permutations
from collections import defaultdict

def main(input:str) -> tuple:
	rules = defaultdict(int)
	pool = set()
	for l in input.splitlines():
		spl = l.split()
		rules[(spl[0], spl[-1][:-1])]+= int(spl[3]) * (-1 if spl[2] == "lose" else 1)
		rules[(spl[-1][:-1], spl[0])]+= int(spl[3]) * (-1 if spl[2] == "lose" else 1)
		pool.add(spl[0])
	p1 = 0
	for p in permutations(pool):
		score = 0
		for i in range(len(p)-1, -1, -1):
			score+=rules[(p[i], p[i-1])]
		p1 = max(p1, score)
	pool.add("me")
	p2 = 0
	for p in permutations(pool):
		score = 0
		for i in range(len(p)-1, -1, -1):
			score+=rules[(p[i], p[i-1])]
		p2 = max(p2, score)
	return (p1, p2)