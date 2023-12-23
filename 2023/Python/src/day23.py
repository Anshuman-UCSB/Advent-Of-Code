P = complex

directions = (-1j,1,1j,-1)
slopes = dict(zip("^>v<",directions))
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

		self.nodes[start] = Node(start)
		self.nodes[end] = Node(end)
		self.start = self.nodes[start]
		self.end = self.nodes[end]

		for p,n in self.nodes.items():
			for d in directions:
				if p+d in self.nodes:
					self.nodes[p+d].edges[n]=1	
					n.edges[self.nodes[p+d]]=1
		if part1:
			for p,n in self.nodes.items():
				if n.direction == None: continue
				if p+n.direction in self.nodes:
					del self.nodes[p+n.direction].edges[n]
		self.compress()
	def compress(self):
		deleted = []
		for n in self.nodes.values():
			if n.direction is not None: continue
			if len(n.edges) == 2 and not any(e.direction for e in n.edges):
				deleted.append(n.pos)
				n1,n2 = n.edges.keys()
				del n1.edges[n]
				del n2.edges[n]
				n1.edges[n2] = sum(n.edges.values())
				n2.edges[n1] = sum(n.edges.values())
	def solve(self):
		ans = 0
		S = [(self.start, 0, [])]
		while S:
			n, dist, seen = S.pop(-1)
			if n == self.end:
				ans = max(dist, ans)
			for e in n.edges:
				if e not in seen:
					S.append((e, dist+n.edges[e], seen[:]+[e]))
		return ans
			
class Node:
	def __init__(self, pos):
		self.pos = pos
		self.edges = {}
		self.direction = None
	def __repr__(self):
		return str(self.pos)

def main(input):
	grid = {}
	for y,r in enumerate(input.splitlines()):
		for x,v in enumerate(r):
			grid[P(x,y)] = v
			if y == 0 and v == '.':
				start = P(x,y)
			if y == len(input.splitlines())-1 and v == '.':
				end = P(x,y)
	g = Graph(grid, start, end,True)
	g2 = Graph(grid, start, end,False)
	return g.solve(), g2.solve()