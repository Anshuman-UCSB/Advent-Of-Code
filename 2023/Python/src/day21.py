P = complex
class Grid:
	def __init__(self, input, part1):
		self.part1 = part1
		self.mX, self.mY = len(input.splitlines()[0]), len(input.splitlines())
		self.grid = set()
		self.positions = set()
		for y, l in enumerate(input.splitlines()):
			for x, v in enumerate(l):
				if v == "#":
					self.grid.add(P(x,y))
				elif v == 'S':
					self.positions.add(P(x,y))
	def step(self):
		newPos = set()
		for p in self.positions:
			for d in (1,-1,1j,-1j):
				if p+d not in self.grid and self.inBounds(p+d):
					newPos.add(p+d)
		self.positions = newPos
	def inBounds(self, p):
		return 0<=p.real<self.mX and 0<=p.imag<self.mY

def main(input):
	g = Grid(input, True)
	for _ in range(64):
		g.step()
	print(len(g.positions))
	return len(g.positions), None