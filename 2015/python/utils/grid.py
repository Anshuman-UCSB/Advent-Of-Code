from collections import deque

class GridType:
	def at(self, crd) -> bool: #return true if wall
		pass

	def getNeighbors(self, crd) -> list:
		return [
			(crd[0]+1, crd[1]),
			(crd[0], crd[1]+1),
			(crd[0]-1, crd[1]),
			(crd[0], crd[1]-1)
		]

	def bfs(self, start, end) -> (int, list):
		cache = set()
		q = deque()
		q.append((0,start, [start]))
		while(len(q)>0):
			s, t, pth = q.pop()
			if self.at(t): continue
			if(t not in cache):
				cache.add(t)
				if(t == end):
					return (s, pth)
				for n in self.getNeighbors(t):
					if not self.at(n):
						tp = pth.copy()
						tp.append(n)
						q.appendleft((s+1, n, tp))
		return (-1,[])
				
	def getReachable(self, start, steps) -> int:
		cache = set()
		q = deque()
		q.append((0,start))
		out = 0
		while(len(q)>0):
			s, t = q.pop()
			if self.at(t): continue
			if(t not in cache):
				cache.add(t)
				if(s > steps):
					return out
				else:
					out+=1
				for n in self.getNeighbors(t):
					if not self.at(n):
						q.appendleft((s+1, n))
		return out