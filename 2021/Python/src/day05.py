from utils.aocUtils import *

def main(input:str):
	points, points2 = defaultdict(int),defaultdict(int)
	for l in input.splitlines():
		x1, y1, x2, y2 = readNums(l)
		x, y = crd2im(x1, y1), crd2im(x2, y2)
		d = imNorm(y-x)
		for p in crange(x, y+d, d):
			if x1 == x2 or y1 == y2:
				points[p]+=1
			points2[p]+=1

	p1 = sum(v>1 for v in points.values())
	p2 = sum(v>1 for v in points2.values())
	return (p1, p2)