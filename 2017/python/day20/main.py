import re
from collections import defaultdict
import math
class particle:
	def __init__(self, line):
		nums=list(map(int,re.findall("-?\d+",line)))
		self.x=nums[:3]
		self.v=nums[3:6]
		self.a=nums[6:9]
	def originDist(self,t):
		return sum(abs(self.a[i]/2*t**2 + self.v[i]*t+self.x[i]) for i in range(3))

def intersectionTimes(p1,p2):
	times = [None for _ in range(3)]
	for i in range(3):
		a = p1.a[i]-p2.a[i]
		b = p1.v[i]-p2.v[i]
		c = p1.x[i]-p2.x[i]
		# Use Muller's method to avoid division by 0
		roots = []
		if a == 0 and b != 0:
			t = -c/b
			if t>=0:
				times[i]={t}
		else:
			for sgn in (-1,1):
				try:
					if b**2-4*a*c >= 0:
						t = (-b + sgn*math.sqrt(b**2-4*a*c))/(2*a)
						if t >= 0:
							roots.append(t)
				except ZeroDivisionError:
					pass
			if roots:
				times[i] = set(roots)
	everything = set()
	for t_set in times:
		if t_set is not None:
			everything|=t_set
	for i in range(3):
		if times[i] is None:
			times[i] = everything
	return {int(v) for v in times[0]&times[1]&times[2] if int(v) == v }

def day20(input):
	particles = [particle(l) for l in input.splitlines()]
	best=float('inf')
	p1 = None
	LONG_TIME=1e100
	for i,p in enumerate(particles):
		if (t:=p.originDist(LONG_TIME)) < best:
			best = t
			p1 = i
	intersections = defaultdict(list)
	for i in range(len(particles)-1):
		for j in range(i+1,len(particles)):
			ins = intersectionTimes(particles[i],particles[j])
			for v in ins:
				intersections[v].append((i,j))
	print(intersections)
	return [p1,None]