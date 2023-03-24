import re
from collections import defaultdict
import math
class particle:
	def __init__(self, line):
		nums=list(map(int,re.findall("-?\d+",line)))
		self.x=nums[:3]
		self.v=nums[3:6]
		self.a=nums[6:9]
	def posAtTime(self,t):
		return tuple(self.a[i]/2*t**2 + self.v[i]*t+self.x[i] for i in range(3))
	def originDist(self,t):
		return sum(abs(self.a[i]/2*t**2 + self.v[i]*t+self.x[i]) for i in range(3))
	def __repr__(self):
		return str(self.x+self.v+self.a)

def zeros(a,b,c):
	if a == b == c == 0:
		return None
	if a == 0:
		if b == 0:
			return set()
		else:
			t = -c/b
			return {int(t)} if t==int(t) and t>= 0 else set()
	else:
		det = b**2 - 4*a*c
		if det >= 0:
			pot = {
				(-b + math.sqrt(b**2 - 4*a*c))/(2*a),
				(-b - math.sqrt(b**2 - 4*a*c))/(2*a),
			}
			return {int(v) for v in pot if v == int(v) and v >= 0}
		else:
			return set()


def intersectionTimes(p1,p2):
	times = [None for _ in range(3)]
	for i in range(3):
		a = (p1.a[i]-p2.a[i])/2
		b = p1.v[i]-p2.v[i]
		c = p1.x[i]-p2.x[i]
		# print("ABC",a,b,c)
		# Use Muller's method to avoid division by 0
		times[i]=zeros(a,b,c)
	# print(times)
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
	# print(particles[13],particles[14])
	# print(particles[13].posAtTime(12),particles[14].posAtTime(12))
	# print(intersectionTimes(particles[13],particles[14]))
	# return None,None
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
	alive = set(range(len(particles)))
	for t,v in sorted(intersections.items()):
		# if t == 0: continue
		collided = set()
		for a,b in v:
			if a in alive and b in alive:
				collided|={a,b}
				# print(a,b,"have collided")
		alive-=collided
		if collided:
			print(t,collided)
	print(len(alive))
	return [p1,None]