import re
from sympy import Symbol, solve_poly_system
class Hailstone:
	def __init__(self,line):
		x,y,z,vx,vy,vz = map(int,re.findall(r"-?\d+",line))
		self.p = [x,y,z]
		self.v = [vx,vy,vz]
		# y(t) = vy*t + y
		# x(t) = vx*t + x
	def __repr__(self):
		return f"({self.p} {self.v})"
	# https://stackoverflow.com/a/20677983/3889449
	def line_intersection(self, other):
		x,y,_ = self.p
		dx,dy,_ = self.v
		line1 = ((x,y),(x+dx,y+dy))
		x,y,_ = other.p
		dx,dy,_ = other.v
		line2 = ((x,y),(x+dx,y+dy))
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
		if self.getTime(x) and other.getTime(x):
			return x, y
		return None, None
	def getTime(self, nX):
		x = self.p[0]
		dx = self.v[0]
		return (nX-x)/dx >= 0

def p2(hailstones):
	x,y,z,vx,vy,vz = (Symbol(c) for c in "x,y,z,vx,vy,vz".split(','))
	p = [x,y,z]
	v = [vx,vy,vz]
	vars = [*p, *v]
	eqs = []
	for i,hs in enumerate(hailstones[:3]):
		t = Symbol(f"t_{i}")
		for j in range(3):
			eqs.append(p[j]+v[j]*t - (hs.p[j] + hs.v[j]*t))
		vars.append(t)
	return int(sum(solve_poly_system(eqs, vars)[0][:3]))
def main(input):
	test_area = (7,27) if len(input.splitlines())<10 else (200000000000000, 400000000000000)
	hailstones = [Hailstone(l) for l in input.splitlines()]
	p1 = 0
	for i in range(len(hailstones)-1):
		for j in range(i+1, len(hailstones)):
			x,y = hailstones[i].line_intersection(hailstones[j])
			if x is None: continue
			if all((test_area[0]<=v<=test_area[1] for v in (x,y))):
				p1 += 1
	return p1, p2(hailstones)