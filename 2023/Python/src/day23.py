P = complex

directions = (-1j,1,1j,-1)
slopes = dict(zip("^>v<", directions))

class Graph:
	def __init__(self, grid, start, end, part1):
		self.nodes = {}
		for p,v in grid.items():
			if v == '.':
				self.nodes[p] = Node(p)
			if v in slopes:
				self.nodes[p] = Node(p)
				if part1:
					self.nodes[p].direction = slopes[v]

		self.start = self.nodes[start]
		self.end = self.nodes[end]

		for p,n in self.nodes.items():
			for d in directions:
				if p+d in self.nodes:
					if self.nodes[p+d].direction in (None, d):
						n.edges[self.nodes[p+d]] = 1
		self.compress()
	def solve(self):
		ans = 0
		S = [(self.start, 0, [])]
		while S:
			n,dist,seen = S.pop(-1)
			if n == self.end:
				ans = max(ans, dist)
			for e in n.edges:
				if e not in seen:
					S.append((e, dist+n.edges[e], seen+[e])) # check here if fails
		return ans
	def compress(self):
		for n in self.nodes.values():
			if n.direction is not None: continue
			if len(n.edges) == 2 and not any(e.direction for e in n.edges):
				n1, n2 = n.edges.keys()
				del n1.edges[n]
				del n2.edges[n]
				n1.edges[n2] = sum(n.edges.values())
				n2.edges[n1] = sum(n.edges.values())

class Node:
	def __init__(self, pos):
		self.pos = pos
		self.edges = {}
		self.direction = None

def main(input):
	grid = {}
	for y,r in enumerate(input.splitlines()):
		for x,v in enumerate(r):
			grid[P(x,y)] = v
			if y == 0 and v == '.':
				start = P(x,y)
			if y == len(input.splitlines())-1 and v == '.':
				end = P(x,y)
	
	return Graph(grid, start, end, True).solve(), Graph(grid, start, end, False).solve()