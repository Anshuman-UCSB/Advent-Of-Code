#game of life

class GameOfLife:
	def __init__(self, input, alive = '#'):
		self.state = set()
		spl = input.splitlines()
		for y, r in enumerate(spl):
			for x, v in enumerate(r):
				if v == alive:
					self.state.add((x,y))
		# print(self.state)
	
	def iter(self):
		consider = set()
		for coord in self.state:
			consider.add(coord)
			for n in self.getNeighbors(coord):
				consider.add(n)
		nState = set()
		for c in consider:
			# print(self.state)
			nCount = sum([1 for x in self.getNeighbors(c) if x in self.state])
			# print(c, nCount)
			
			if self.logic(c in self.state, nCount):
				nState.add(c)
		self.state = nState

	def inBound(self, coord):
		return True
	
	def logic(self, alive, count):
		if alive:
			return count == 2 or count == 3
		else:
			return count == 3

	def getNeighbors(self, coord):
		out = []
		for dx,dy in [(0,1),(0,-1),
					  (1,0),(1,1),(1,-1),
					  (-1,0),(-1,1),(-1,-1)]:
			t = (coord[0]+dx, coord[1]+dy)
			if self.inBound(t):
				out.append(t)
		return out
	
	def score(self):
		return len(self.state)