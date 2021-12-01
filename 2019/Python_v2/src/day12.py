from utils.aocUtils import *

class planet:
	def __init__(self, inp):
		self.p = readNums(inp)
		self.v = [0]*3

	def hash(self):
		return f"{self.p}-{self.v}"

	def getEnergy(self):
		return sum([abs(x) for x in self.p]) * sum([abs(x) for x in self.v])
	
	def update(self, p2):
		for i in range(3):
			if(p2.p[i]>self.p[i]):
				self.v[i]+=1
			elif(p2.p[i]<self.p[i]):
				self.v[i]-=1
	
	def move(self):
		for i in range(3):
			self.p[i]+=self.v[i]

def iter(planets):
	for p in planets:
		for p2 in planets:
			p.update(p2)
	for p in planets:
		p.move()

def hashAll(planets):
	return str([p.hash() for p in planets])

def solveAxis(input, axis):
	planets = [planet(l) for l in input.splitlines()]
	for p in planets:
		for i in range(3):
			if i != axis:
				p.p[i] = 0
	start = hashAll(planets)
	time = 0
	state = hashAll(planets)
	while state != start or time == 0:
		time+=1
		iter(planets)
		state = hashAll(planets)
	return time

def main(input:str):
	planets = [planet(l) for l in input.splitlines()]
	for _ in range(1000):
		iter(planets)
	p1 = (sum([x.getEnergy() for x in planets]))
	p2 = reduce(lcm, [solveAxis(input, i) for i in range(3)])
	return (p1, p2)