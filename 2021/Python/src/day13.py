from utils.aocUtils import *

def foldx(points, x):
	out = set()
	for p in points:
		if p.real > x:
			out.add(int(x-(p.real-x))+int(p.imag)*1j)
		else:
			out.add(p)
	return out
def foldy(points, y):
	out = set()
	for p in points:
		if p.imag > y:
			out.add(int(p.real)+int(y-(p.imag-y))*1j)
		else:
			out.add(p)
	return out

def main(input:str):
	p1 = 0
	points = set()
	pts = True
	for l in input.splitlines():
		if l == "":
			pts = False
			continue
		if pts:
			nums = readNums(l)
			points.add(nums[0]+nums[1]*1j)
		else:
			if l.split()[2][0] == 'y':
				points = foldy(points, readNums(l)[0])
				if p1 == 0:
					p1 = len(points)
			else:
				points = foldx(points, readNums(l)[0])
				if p1 == 0:
					p1 = len(points)
	
	return (p1, printSet(points))