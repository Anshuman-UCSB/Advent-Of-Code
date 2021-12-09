from utils.aocUtils import *

def getNeighbors(p):
	return [p+1, p-1, p+1j, p-1j]

def lowPoint(points, p):
	for n in getNeighbors(p):
		if n in points and points[n]<=points[p]:
			return False
	return True

def main(input:str):
	points = gridify(input, int)
	p1 = sum(points[p]+1 for p in points if lowPoint(points, p))
	sets = finiteGrid(points).connComponents(lambda a, b: a!=9 and b!=9)
	return (p1, prod(sorted([len(x) for x in sets])[-3:]))