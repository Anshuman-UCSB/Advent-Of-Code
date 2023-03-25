from collections import defaultdict
def day24(input):
	parts = []
	for l in input.splitlines():
		parts.append(tuple(map(int,l.split('/'))))
	possibles = defaultdict(list)
	for id,(a,b) in enumerate(parts):
		possibles[a].append(id)
		possibles[b].append(id)

	p1 = -1
	p2len = 0
	p2 = -1
	def dfs(need, containing):
		nonlocal p1,p2,p2len
		continued = False
		for potential_id in possibles[need]:
			if potential_id not in containing:
				dfs(parts[potential_id][0 if parts[potential_id][1]==need else 1],containing|{potential_id})
				continued = True
		if not continued:
			strength = 0
			for id in containing:
				strength+=sum(parts[id])
			p1 = max(p1, strength)
			if len(containing)>p2len or (len(containing)==p2len and strength > p2):
				p2len = len(containing)
				p2 = strength
		# print("valid bridge of", containing)
	dfs(0,set())
	return [p1,p2]