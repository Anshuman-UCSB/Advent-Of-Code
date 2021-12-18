from utils.aocUtils import *

p1, p2 = 0, 0
def main(input:str):
	neighbors = defaultdict(list)
	for l,r in [x.split('-') for x in input.splitlines()]:
		neighbors[l].append(r)
		neighbors[r].append(l)
	def bfs(seen, pos, doublevisit):
		global p1, p2
		if pos == "end":
			p1 += doublevisit == False
			p2 += 1
			return
		if pos in seen:
			if pos == "start": return
			if pos.islower():
				if doublevisit == False:
					doublevisit = True
				else:
					return
		for n in neighbors[pos]:
			bfs(seen+[pos], n, doublevisit)
	bfs([], "start", False)
	return p1, p2