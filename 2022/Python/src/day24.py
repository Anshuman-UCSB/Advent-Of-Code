from utils.aocUtils import *
from collections import defaultdict
P = complex
unpack = lambda x: (int(x.real), int(x.imag))

class Grid:
	def __init__(self, inp):
		inp=inp.strip()
		self.grid = defaultdict(list)
		lines = inp.splitlines()
		self.w, self.h = len(lines[0]), len(lines)
		self.end = P(self.w-2,self.h-3)
		self.grid[self.end]+='E'
		translation = {'v':1j,'^':-1j,'>':1,'<':-1}
		for y,row in enumerate(lines):
			for x, val in enumerate(row):
				if val in translation:
					self.grid[P(x-1,y-1)].append(translation[val])
	def __str__(self,highlight=set()):
		translation = {1j:'v',-1j:'^',1:'>',-1:'<'}
		out = "GRID:\n#."+"#"*(self.w-2)+'\n'
		for y in range(self.h-2):
			out+='#'
			for x in range(self.w-2):
				p = P(x,y)
				if p in highlight:
					out+='@'
				else:
					if len(self.grid[p]) == 0:
						out+='.'
					elif len(self.grid[p]) == 1:
						out+=translation[self.grid[p][0]]
					else:
						out+=str(len(self.grid[p]))
			out+='#\n'
		out+="#"*(self.w-2)+'.#'
		return out
	def wrap(self, p):
		return P(p.real % (self.w-2),p.imag % (self.h-2))

	def iter(self):
		n_grid = defaultdict(list)
		for y in range(self.h-2):
			for x in range(self.w-2):
				p = P(x,y)
				for v in self.grid[p]:
					n_grid[self.wrap(p+v)].append(v)
		self.grid = n_grid
	def inBounds(self, p):
		if p == -1j or p == self.end:
			return True
		x,y = unpack(p)
		return 0<=x<self.w-2 and 0<=y<self.h-2

	def p1(self):
		p = P(0,-1)
		q = {p}
		t = 0
		dirs = [1,-1,1j,-1j,0]
		while True:
			t+=1
			self.iter()
			pot = {i+d for i in q for d in dirs}
			if self.end in pot:
				self.p1Ans = t
				return t
			pot = list(filter(self.inBounds, pot))
			q = []
			for i in pot:
				if len(self.grid[i])==0:
					q.append(i)
	def p2(self):
		p = self.end
		q = {p}
		t = self.p1Ans
		dirs = [1,-1,1j,-1j,0]
		while True:
			t+=1
			self.iter()
			pot = {i+d for i in q for d in dirs}
			if -1j in pot:
				return t+self.p1()
			pot = list(filter(self.inBounds, pot))
			q = []
			for i in pot:
				if len(self.grid[i])==0:
					q.append(i)

def main(input:str):
	p1 = p2 = 0
	g = Grid(input)
	return (g.p1(), g.p2())