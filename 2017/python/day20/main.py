import re
from collections import defaultdict
class particle:
	id=0
	def __init__(self, line):
		self.id=particle.id
		particle.id+=1
		nums=list(map(int,re.findall("-?\d+",line)))
		self.x=nums[:3]
		self.v=nums[3:6]
		self.a=nums[6:9]
	def posAtTime(self,t):
		return tuple(self.a[i]/2*t**2 + self.v[i]*t+self.x[i] for i in range(3))

	def totalAcceleration(self):
		return sum(abs(a) for a in self.a)
	def position(self):
		return tuple(self.x)
	def iter(self):
		for i in range(3):
			self.v[i]+=self.a[i]
		for i in range(3):
			self.x[i]+=self.v[i]
	def __repr__(self):
		return str(self.x+self.v+self.a)


def dist(a, b):
	return sum(abs(i-j) for i,j in zip(a,b))

def buildDistances(particles):
	l = []
	for i in range(len(particles)-1):
		for j in range(i+1,len(particles)):
			l.append(dist(particles[i].position(),particles[j].position()))
	return l

def gettingCloser(before,after):
	if len(before) != len(after):
		return True
	for i in range(len(before)):
		if after[i]<before[i]:
			return True
	return False

def day20(input):
	particles = [particle(l) for l in input.splitlines()]
	best = float('inf')
	bestInd = -1
	for i,p in enumerate(particles):
		if p.totalAcceleration()<best:
			bestInd = i
			best = p.totalAcceleration()
	old=[]
	dists = buildDistances(particles)
	t=0
	while gettingCloser(old,dists):
		for p in particles:
			p.iter()
		t+=1
		positions = defaultdict(set)
		for i, p in enumerate(particles):
			positions[p.position()].add(i)
		collisions = set()
		for l in positions.values():
			if len(l)>1:
				collisions|=l
		particles = [p for i,p in enumerate(particles) if i not in collisions]
		old = dists
		dists = buildDistances(particles)

	return [bestInd,len(particles)]

if __name__=="__main__":
	import sys
	print(day20(open(sys.argv[1],'r').read()))