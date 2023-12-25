from collections import defaultdict

class Graph:
	def __init__(self, G):
		self.G = G
		self.parent = {n:None for n in self.G}

	def bfs(self, s, t):
		self.parent = {n:None for n in self.G}
		self.parent[s] = s
		Q = [s]
		while Q:
			n = Q.pop(0)
			for e, c in self.G[n].items():
				if c > 0 and self.parent[e] is None:
					self.parent[e] = n
					Q.append(e)
		return self.parent[t] is not None
	def minCut(self, s, t):
		for v, E in self.G.items():
			for k in E:
				self.G[v][k] = 1
		maxFlow = 0
		while self.bfs(s,t):
			flow = float('inf')
			n = t
			while n != s:
				flow=min(flow, self.G[self.parent[n]][n])
				n = self.parent[n]

			maxFlow+=flow

			v = t
			while v != s:
				u = self.parent[v]
				self.G[u][v] -= flow
				self.G[v][u] += flow
				v = u
		return maxFlow
	def solve(self):
		size1 = len({n for n,p in self.parent.items() if p})
		return (len(self.G)-size1)*size1

def main(input):
	G = defaultdict(dict)
	for l in input.splitlines():
		lhs, rhs = l.split(": ")
		for r in rhs.split():
			G[lhs][r]=1
			G[r][lhs]=1
	graph = Graph(G)
	s,*other = graph.G
	for t in other:
		if graph.minCut(s,t) == 3:
			break
	return graph.solve(), None