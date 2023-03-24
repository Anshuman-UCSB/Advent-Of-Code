import re
from collections import defaultdict
import math
class particle:
	def __init__(self, line):
		nums=list(map(int,re.findall("-?\d+",line)))
		self.x=nums[:3]
		self.v=nums[3:6]
		self.a=nums[6:9]
	def at(self,t):
		return tuple(map(int,(self.a[i]/2*t**2 + self.v[i]*t+self.x[i] for i in range(3))))
	def originDist(self,t):
		return sum(abs(self.a[i]/2*t**2 + self.v[i]*t+self.x[i]) for i in range(3))
	def __repr__(self):
		return str(self.x+self.v+self.a)

def filtered(s):
	if s is None:
		return None
	return {int(v) for v in s if int(v) == v and v >= 0}

def zeros(a,b,c):
	if a==b==c==0:
		return None
	if a == 0:
		if b != 0:
			return filtered({-c/b})
		else:
			return set()
	else:
		det = b**2 - 4*a*c
		if det>=0:
			return filtered({(-b+math.sqrt(det))/2*a,(-b-math.sqrt(det))/2*a})
		else:
			return set()

def intersectionTimes(p1,p2):
	times = []
	for i in range(3):
		a = (p1.a[i]-p2.a[i])/2
		b = (p1.v[i]-p2.v[i])+(p1.a[i]-p2.a[i])/2
		c = (p1.x[i]-p2.x[i])
		print(a,b,c)
		times.append(zeros(a,b,c))
	return times
def day20(input):
	particles = [particle(l) for l in input.splitlines()]
	print(particles[0].at(9),particles[1].at(9))
	print(particles[0].at(10),particles[1].at(10))
	print(particles[0].at(11),particles[1].at(11))
	dists = [sum(map(abs,p.at(1e99))) for p in particles]
	p1 = dists.index(min(dists))
	for i in range(len(particles)-1):
		for j in range(i+1,len(particles)):
			print(intersectionTimes(particles[i],particles[j]))
	return [p1,None]