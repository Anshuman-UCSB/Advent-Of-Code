import re
from sympy import Symbol, solve_poly_system
class Hailstone:
	def __init__(self, line):
		x,y,z,vx,vy,vz = map(int, re.findall(r"-?\d+",line))
		self.p = [x,y,z]
		self.v = [vx,vy,vz]
	def line_intersection(self, other):
		x,y,_ = self.p
		vx,vy,_ = self.v
		line1 = ((x,y), (x+vx, y+vy))
		x,y,_ = other.p
		vx,vy,_ = other.v
		line2 = ((x,y), (x+vx, y+vy))
		xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
		ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

		def det(a, b):
			return a[0] * b[1] - a[1] * b[0]

		div = det(xdiff, ydiff)
		if div == 0:
			return None, None

		d = (det(*line1), det(*line2))
		x = det(d, xdiff) / div
		y = det(d, ydiff) / div
		if self.isInFuture(x) and other.isInFuture(x):
			return x, y
		return None, None
	def isInFuture(self, nX):
		x = self.p[0]
		vx = self.v[0]
		return (nX - x)/vx >= 0

def p2(hailstones):
	x,y,z,vx,vy,vz = (Symbol(c) for c in "x,y,z,vx,vy,vz".split(','))
	p = [x,y,z]
	v = [vx,vy,vz]
	vars = [*p, *v]
	eqs = []
	for i, hs in enumerate(hailstones[:3]):
		t = Symbol(f"t_{i}")
		for j in range(3):
			eqs.append(p[j]+v[j]*t - (hs.p[j] + hs.v[j]*t))
		vars.append(t)
	return int(sum(solve_poly_system(eqs, vars)[0][:3]))

def main(input):
	hailstones = [Hailstone(l) for l in input.splitlines()]
	ta = (7,27) if len(input.splitlines()) < 10 else (200000000000000,400000000000000)
	p1 = 0
	for i in range(len(hailstones)-1):
		for j in range(i+1, len(hailstones)):
			x,y = hailstones[i].line_intersection(hailstones[j])
			if x is None: continue
			if ta[0]<=x<=ta[1] and ta[0]<=y<=ta[1]:
				p1 += 1
	return p1, p2(hailstones)