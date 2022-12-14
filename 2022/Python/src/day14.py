from utils.aocUtils import *

class Grid:
	def __init__(self,inp):
		self.xlim = [500,500]
		self.ylim = [0,0]
		self.grid = {(500,0):'+'}
		for l in inp.splitlines():
			spl = l.split()
			for i in range(0,len(spl)-2,2):
				self.populate(spl[i], spl[i+2])
	def populate(self, start, end):
		x1, y1 = map(int,start.split(","))
		x2, y2 = map(int,end.split(","))
		self.xlim[0] = min(self.xlim[0], x1, x2)
		self.xlim[1] = max(self.xlim[1], x1, x2)
		self.ylim[0] = min(self.ylim[0], y1, y2)
		self.ylim[1] = max(self.ylim[1], y1, y2)
		if x1 == x2:
			for y in range(min(y1, y2), max(y1, y2)+1):
				self.grid[(x1,y)] = '#'
		else:
			for x in range(min(x1, x2), max(x1, x2)+1):
				self.grid[(x,y1)] = '#'
	def print(self):
		for y in range(self.ylim[0], self.ylim[1]+6):
			for x in range(self.xlim[0]-5, self.xlim[1]+6):
				print(self.grid.get((x,y), '.'),end="")
			print()
	def iter(self):
		pos = [500,1]
		while True:
			while tuple(pos) not in self.grid:
				pos[1]+=1
				if pos[1]-3 >= self.ylim[1]:
					return False
			if (pos[0]-1, pos[1]) not in self.grid:
				pos[0]-=1
				continue
			elif (pos[0]+1, pos[1]) not in self.grid:
				pos[0]+=1
				continue
			else:
				self.grid[(pos[0], pos[1]-1)] = 'o'
				return (pos[0], pos[1]-1) != (500,0)
		self.grid[tuple(pos)] = 'o'
	def p2init(self):
		for x in range(self.xlim[0]-self.ylim[1], self.xlim[1]+self.ylim[1]+1):
			self.grid[(x,self.ylim[1]+2)] = '#'
		self.xlim[0] -= self.ylim[1]
		self.xlim[1] += self.ylim[1]
def main(input:str):
	p1 = 0
	grid = Grid(input)
	while grid.iter():
		p1+=1
	p2=p1+1
	grid.p2init()
	while grid.iter():
		p2+=1
	return (p1, p2)