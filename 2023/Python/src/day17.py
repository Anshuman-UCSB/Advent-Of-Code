import heapq # min heap
P = complex

class State:
	def __init__(self, loss, p, d, c):
		self.loss = loss
		self.p = p
		self.d = d
		self.c = c
		self.key = (self.p, self.d, self.c)
	def __lt__(self, other):
		return (self.loss, self.c)<(other.loss, other.c)

def main(input):
	grid = {}
	for y, r in enumerate(input.splitlines()):
		for x,v in enumerate(r):
			grid[P(x,y)] = int(v)
	shape = len(input.splitlines())
	end = P(len(input.splitlines()[0])-1, shape-1)
	
	def solve(part1):
		seen = set()
		Q = [State(0,0,1,0), State(0,0,1j,0)]
		while Q:
			s = heapq.heappop(Q)
			if s.key in seen:
				continue
			seen.add(s.key)
			loss, p, d, c = s.loss, s.p, s.d, s.c

			if p == end and (part1 or c>=4):
				return loss
			# if p not in grid:
			# 	continue
			if ((part1 and c<3) or (not part1 and c<10)) and p+d in grid:
				heapq.heappush(Q, State(loss+grid[p+d], p+d, d, c+1))
			
			d *= 1j
			if (part1 or 4<=c) and p+d in grid:
				heapq.heappush(Q, State(loss+grid[p+d], p+d, d, 1))
			d *= -1
			if (part1 or 4<=c) and p+d in grid:
				heapq.heappush(Q, State(loss+grid[p+d], p+d, d, 1))

	return solve(True), solve(False)