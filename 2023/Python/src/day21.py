import numpy as np
P = complex
class Grid:
	def __init__(self, input):
		self.size = len(input.splitlines())
		self.grid = set()
		self.positions = {}
		self.frontier = set()
		self.parity = False
		for y, l in enumerate(input.splitlines()):
			for x, v in enumerate(l):
				if v == '#':
					self.grid.add(P(x,y))
				if v == 'S':
					self.positions[P(x,y)]=self.parity
					self.frontier.add(P(x,y))
	def score(self):
		return sum(v==self.parity for v in self.positions.values())
	def step(self):
		newFrontier = set()
		self.parity = not self.parity
		for p in self.frontier:
			for d in (1,-1,1j,-1j):
				if self.wrap(p+d) not in self.grid and p+d not in self.positions:
					newFrontier.add(p+d)
					self.positions[p+d] = self.parity
		self.frontier = newFrontier
	def wrap(self, p):
		return P(p.real%self.size, p.imag%self.size)

def main(input):
	g = Grid(input)
	# f(x) = how many squares are visited at time 65 + 131*x
	X,Y = [0,1,2], []
	target = (26501365 - 65)//131
	for s in range(65 + 131*2 + 1):
		if s%131 == 65:
			Y.append(g.score())
		if s == 64:
			p1 = g.score()
		g.step()
	poly = np.rint(np.polynomial.polynomial.polyfit(X,Y,2)).astype(int).tolist()
	return p1, sum(poly[i]*target**i for i in range(3))