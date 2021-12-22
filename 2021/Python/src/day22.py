from utils.aocUtils import *

class Cube:
	def __init__(self, lx,ly,lz ,hx,hy,hz):
		self.bounds = [lx,ly,lz ,hx,hy,hz]
		self.points = [
			(lx, ly, lz),
			(lx, ly, hz),
			(lx, hz, lz),
			(lx, hz, hz),
			(hx, ly, lz),
			(hx, ly, hz),
			(hx, hz, lz),
			(hx, hz, hz),
		]
	def __str__(self):
		return f"Cube from ({self.bounds[:3]}) to ({self.bounds[3:]})"
	def containsPoint(self, p):
		for i in range(3):
			if not(self.bounds[i]<=p[i]<=self.bounds[i+3]):
				return False
		return True
	def intersect(self, c):
		for p in self.points:
			if c.containsPoint(p):
				return True
		for p in c.points:
			if self.containsPoint(p):
				return True
		return False

def remove(base, cut):
	if not base.intersect(cut):
		return False, []
	cases = []
	ranges = []
	for i in range(3):
		ranges.append([])
		cutlow, cuthigh = cut.bounds[i::3]
		baselow, basehigh = base.bounds[i::3]
		match cutlow<=baselow, basehigh<=cuthigh:
			case True, True: cases.append("spanning"); 
			case True, False: cases.append("left"); ranges[-1].append([cuthigh, basehigh])
			case False, True: cases.append("right"); ranges[-1].append([baselow, cutlow])
			case False, False: cases.append("inner"); ranges[-1].append([baselow, cutlow]); ranges[-1].append([cuthigh, basehigh])
	blx, bly, blz, bhx, bhy, bhz = base.bounds
	clx, cly, clz, chx, chy, chz = cut.bounds
	print(ranges)
	match len(ranges[0]), len(ranges[1]), len(ranges[2]):
		case 0, 0, 0: return True, [] # no cubes, fully spanning
		case 0, 0, _: return True, [Cube(blx, bly, r[0], bhx, bhy, r[1]) for r in ranges[2]]
		case 0, _, 0: return True, [Cube(blx, r[0], blz, bhx, r[1], bhz) for r in ranges[1]]
		case _, 0, 0: return True, [Cube(r[0],bly, blz, r[1], bhy, bhz) for r in ranges[0]]
		case _, _, 0: return True, [Cube(rx[0],ry[0], blz, rx[1], ry[1], bhz) for rx in ranges[0] for ry in ranges[1]]
		case _, 0, _: return True, [Cube(rx[0],bly, rz[0], rx[1], bhy, rz[1]) for rx in ranges[0] for rz in ranges[2]]
	# if cases == ["spanning"]*3:
	# 	return True, []
	# if cases == ["spanning", "spanning", "left"]:
	# 	t = base.bounds[:]
	# 	t[2] = cut.bounds[5]
	# 	return True, [Cube(*t)]
	# if cases == ["spanning", "spanning", "right"]:
	# 	t = base.bounds[:]
	# 	t[5] = cut.bounds[2]
	# 	return True, [Cube(*t)]
	# if cases == ["spanning", "spanning", "inner"]:
	# 	t = base.bounds[:]
	# 	t[5] = cut.bounds[2] # set high z on base to low z of cut
	# 	t2 = base.bounds[:]
	# 	t2[2] = cut.bounds[5]
	# 	return True, [Cube(*t), Cube(*t2)]

def main(input:str):
	p1 = 0
	cubes = []
	p2 = 0
	points = {}
	litCubes = []
	for l in input.splitlines():
		cubes.append([l.split()[0]]+readNums(l))
	# p1cubes = [r for r in cubes if all([abs(x)<=50 for x in r[1:]])]
	# for onoff, lx, hx, ly, hy, lz, hz in p1cubes:
	# 	for x in range(lx, hx+1):
	# 		for y in range(ly, hy+1):
	# 			for z in range(lz, hz+1):
	# 				points[(x,y,z)] = (onoff=="on")
	base = Cube(0,0,0,3,3,3)
	cut = Cube(1,0,1,2,3,5)
	resp, cuts = (remove(base, cut))
	for c in cuts:
		print(c)
	# p1 = sum(points.values())
	return (p1, p2)