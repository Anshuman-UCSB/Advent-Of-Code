from utils.aocUtils import *

class Moon:
	def __init__(self, s):
		self.pos = readNums(s)
		self.vel = [0,0,0]
	def gravity(self, other):
		for i in range(3):
			if self.pos[i]>other.pos[i]:
				self.vel[i]-=1
			elif self.pos[i]<other.pos[i]:
				self.vel[i]+=1
	def gravity1d(self, other, dim):
		if self.pos[dim]>other.pos[dim]:
			self.vel[dim]-=1
		elif self.pos[dim]<other.pos[dim]:
			self.vel[dim]+=1
	def move1d(self, dim):
		self.pos[dim]+=self.vel[dim]
	def move(self):
		for i in range(3):
			self.pos[i]+=self.vel[i]

	def energy(self):
		return sum(map(abs,self.pos))*sum(map(abs,self.vel))

	def __str__(self):
		return f"{self.pos} <{self.vel}>"

def hashDim(moons, dim):
	return ",".join([str(m.pos[dim])+":"+str(m.vel[dim]) for m in moons])

def iter1d(moons, dim):
	for m in moons:
		for k in moons:
			m.gravity1d(k, dim)
	for m in moons:
		m.move1d(dim)

def cycle(input, dim):
	moons = [Moon(x) for x in input.splitlines()]
	cache = {}
	t = 0
	while True:
		h = hashDim(moons, dim)
		if h in cache:
			return (cache[h], t-cache[h])
		cache[h] = t
		t+=1
		iter1d(moons, dim)


def p2s(input):
	cycles = [cycle(input, i)[1] for i in range(3)]
	return reduce(lcm, cycles)


def main(input:str):
	moons = [Moon(x) for x in input.splitlines()]
	for _ in range(1000):
		for m in moons:
			for k in moons:
				m.gravity(k)
		for m in moons:
			m.move()
	p1 = sum([moon.energy() for moon in moons])
	p2 = p2s(input)
	return (p1, p2)