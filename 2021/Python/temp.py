from dataclasses import dataclass
@dataclass
class Point:
	x: int
	y: int
	def __str__(self):
		return f"({self.x}, {self.y})"
class Cube:
	def __init__(self, low, high):
		self.low = low
		self.high = high

	def intersects(self, cube2):
		if cube2.high.x<self.low.x or self.high.x<cube2.low.x:
			return False
		if cube2.high.y<self.low.y or self.high.y<cube2.low.y:
			return False
		return True
	def __str__(self):
		return f"Cube from {self.low} to {self.high}"

def subtract(base, c):
	assert(base.intersects(c))
	c.low.x-=1
	c.low.y-=1
	c.high.x+=1
	c.high.y+=1
	cuts = []
	lambdas = [
		lambda c: c.x,
		lambda c: c.y,
		# lambda c: c.z
	]
	for fn in lambdas:
		bl = fn(base.low)
		bh = fn(base.high)
		cl = fn(c.low)
		ch = fn(c.high)
		match cl<bl, bh<ch:
			case True, True: cuts.append("spn")
			case False, True: cuts.append("rhs")
			case True, False: cuts.append("lhs")
			case False, False: cuts.append("inn")
	print(cuts)
	match cuts:
		case ["spn", "spn"]: return []
		case ["spn", "rhs"]: return [Cube(base.low, Point(base.high.x, c.low.y))]
		case ["spn", "lhs"]: return [Cube(Point(base.low.x, c.high.y), base.high)]
		case ["spn", "inn"]: return [Cube(base.low, Point(base.high.x, c.low.y)), Cube(Point(base.low.x, c.high.y), base.high)]
		case ["rhs", "spn"]: return [Cube(base.low, Point(c.low.x,base.high.y))]
		case ["rhs", "rhs"]: return [Cube(base.low, Point(c.low.x, base.high.y)), Cube(Point(c.high.x, base.low.y), Point(base.high.x, c.low.y))]
		case ["rhs", "lhs"]: return [Cube(Point(base.low.x, c.high.y), base.high)]
		case ["rhs", "inn"]: return [Cube(base.low, Point(base.high.x, c.low.y)), Cube(Point(base.low.x, c.high.y), base.high)]
	print(cuts)

c1 = Cube(Point(0,0), Point(4,4))
c2 = Cube(Point(2,2), Point(4,4))
res = subtract(c1, c2)
if res:
	for l in res:
		print(l)
else:
	print(res)
print(c1.intersects(c2))