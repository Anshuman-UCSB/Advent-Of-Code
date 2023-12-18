class Solver:
	def __init__(self):
		self.perimeter = 0
		self.points = [(0,0)]
		self.pos = [0,0]
	def addInstruction(self, direction, length):
		directions = {"R":(1,0), "D":(0,1), "L":(-1,0), "U":(0,-1),
					  "0":(1,0), "1":(0,1), "2":(-1,0), "3":(0,-1)}
		self.perimeter += length
		d = directions[direction]
		self.pos[0]+=length*d[0]
		self.pos[1]+=length*d[1]
		self.points.append(tuple(self.pos))
	def solve(self):
		area = 0
		for (x1,y1), (x2,y2) in zip(self.points[:-1], self.points[1:]):
			area += (x2-x1)*(y2+y1)
		return abs(int(area))//2 + self.perimeter//2 + 1

def main(input):
	p1 = Solver()
	p2 = Solver()
	for d, l, color in [l.split() for l in input.splitlines()]:
		p1.addInstruction(d, int(l))
		length = color[2:-2]
		direction = color[-2]
		p2.addInstruction(direction, int(length, base=16))
 
	return p1.solve(), p2.solve()