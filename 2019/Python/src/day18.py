from utils.aocUtils import *
from utils.grid import GridType
from collections import deque

class Grid_18(GridType):
	def __init__(self, l):
		self.g = [[c for c in x] for x in l.splitlines()]
		self.target = 0
		for r in self.g:
			for v in r:
				if 'a'<=v<='z':
					self.target+=1
	
	def at(self, crd):
		p, s = crd
		if self.g[p[1]][p[0]] == '#':
			return True
		if 'A'<=self.g[p[1]][p[0]]<='Z':
			return self.g[p[1]][p[0]] not in s
		return False

	def getNeighbors(self, crd):
		p, s = crd
		out = [(n,s.copy()) for n in super().getNeighbors(p)]
		for t in out:
			if 'a'<=self.g[t[0][1]][t[0][0]]<='z':
				t[1].add(self.g[t[0][1]][t[0][0]].upper())
		return out
	
	def p1s(self, start):
		cache = set()
		q = deque()
		q.append((0,start, [start]))
		while(len(q)>0):
			s, t, pth = q.pop()
			# print(s,t)
			if self.at(t): continue
			if((t[0],tuple(sorted(list(t[1])))) not in cache):
				cache.add((t[0],tuple(sorted(list(t[1])))))
				if(len(t[1])==self.target):
					return (s, pth)
				for n in self.getNeighbors(t):
					if not self.at(n):
						tp = pth.copy()
						tp.append(n)
						q.appendleft((s+1, n, tp))
		return (-1,[])

	def p2s(self, start):
		x, y =start
		sets = [set()]
		for i in range(0,y):
			for j in range(0,x):
				c = self.g[i][j]
				if "a"<=c<='z':
					sets[-1].add(c.upper())
		sets.append(set())
		for i in range(0,y):
			for j in range(x, len(self.g[0])):
				c = self.g[i][j]
				if "a"<=c<='z':
					sets[-1].add(c.upper())
		sets.append(set())
		for i in range(y,len(self.g)):
			for j in range(0,x):
				c = self.g[i][j]
				if "a"<=c<='z':
					sets[-1].add(c.upper())
		sets.append(set())
		for i in range(y,len(self.g)):
			for j in range(x, len(self.g[0])):
				c = self.g[i][j]
				if "a"<=c<='z':
					sets[-1].add(c.upper())
		alph = set([c for c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ"])
		starts = [
			((x-1, y-1), alph.difference(sets[0])),
			((x+1, y-1), alph.difference(sets[1])),
			((x-1, y+1), alph.difference(sets[2])),
			((x+1, y+1), alph.difference(sets[3])),
		]
		out = 0
		for s in starts:
			out+=self.p1s(s)[0]
		return out
		

def p2s(input):
	g = Grid_18(input)
	for y, r in enumerate(g.g):
		for x, v in enumerate(r):
			if v == '@':
				g.g[y] = ['#']*len(g.g[y])
				for i in range(len(g.g)):
					g.g[i][x] = '#'
				return g.p2s((x,y))
				
	# for l in g.g:
	# 	print("".join(l))

def main(input:str):
	g = Grid_18(input)
	for y, r in enumerate(g.g):
		for x, v in enumerate(r):
			if v == '@':
				start = (x,y)
	p1 = g.p1s((start, set()))[0] #53 seconds
	return (p1, p2s(input)) #56 seconds