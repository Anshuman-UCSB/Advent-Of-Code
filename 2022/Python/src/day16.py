from utils.aocUtils import *
from collections import defaultdict
from itertools import permutations

def floydwarshall(V, E):
	dist = defaultdict(lambda: defaultdict(lambda: float('inf')))
	for a,b in E:
		dist[a][b] = 1
	for v in V:
		dist[v][v] = 0
	for k in V:
		for i in V:
			for j in V:
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
	return dist

def main(input:str):
	p1 = p2 = 0
	V = []
	nz_V = ['AA']
	flows = {"AA":0}
	E = []
	for l in input.splitlines():
		name, *children = re.findall(r"[A-Z]{2}", l)
		V.append(name)
		E.extend([(name, c) for c in children])

		flow = int(re.findall(r"\d+", l)[0])
		if flow>0:
			nz_V.append(name)
			flows[name] = flow
	dists = floydwarshall(V, E)
	rooms = len(nz_V)

	def dfs(room, t, targets = set(nz_V)):
		targets = targets - {room}
		best = 0
		for r in targets:
			time_left = t - dists[room][r] - 1
			if time_left > 0:
				flow = flows[r]*time_left
				flow += dfs(r, time_left, targets)
				best = max(best, flow)
		return best
	
	endpoints = {}
	def record(room, t=26, flow = 0, seen = set()):
		seen = seen | {room}
		targets = set(nz_V) - seen
		key = frozenset(seen-{'AA'})
		endpoints[key] = max(endpoints.get(key, 0), flow)
		
		best = 0
		for r in targets:
			time_left = t - dists[room][r] - 1
			if time_left > 0:
				new_flow = flows[r]*time_left
				new_flow += record(r, time_left, flow + new_flow, seen)
				best = max(best, new_flow)
		return best
	record('AA')

	def fill(cur=frozenset(set(nz_V) - {"AA"})):
		if cur not in endpoints:
			best = 0
			for e in cur:
				subset = cur-{e}
				new_flow = fill(subset)
				best = max(best, new_flow)
			endpoints[cur] = best
		return endpoints[cur]
	fill()


	total = set(nz_V)-{'AA'}
	for h in endpoints:
		e = frozenset(total-h)
		p2 = max(p2, endpoints[h]+endpoints[e])
		
	return (dfs('AA',30), p2)