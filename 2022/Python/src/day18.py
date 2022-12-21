from utils.aocUtils import *
import numpy as np
def main(input:str):
	p2 = 0
	points = set()
	low, high = np.array([float('inf')]*3), np.array([float('-inf')]*3)
	dirs = [(-1, 0, 0), (1, 0, 0), (0, -1, 0), (0, 1, 0), (0, 0, -1), (0, 0, 1)]
	for l in input.splitlines():
		x,y,z = map(int,(l.split(',')))
		t = np.array([x,y,z])
		low = np.minimum(t, low)
		high = np.maximum(t, high)
		points.add((x, y, z))
	low-=1
	high+=1
	def inBounds(point):
		return all(low[i]<=point[i]<=high[i] for i in range(3))
	
	def flood(frontier, seen = set()):
		if len(frontier) == 0:
			return seen
		t = set()
		for x,y,z in frontier:
			for dx,dy,dz in dirs:
				tmp = (x+dx,y+dy,z+dz)
				if inBounds(tmp) and tmp not in points and tmp not in seen:
					t.add(tmp)
		seen|=t
		flood(t, seen)
		return seen
	outside = flood(set([tuple(low)]))

	p1 = len(points)*6
	for x,y,z in points:
		for dx,dy,dz in dirs:
			if (x+dx,y+dy,z+dz) in points:
				p1-=1
			if (x+dx,y+dy,z+dz) in outside:
				p2+=1
	return (p1, p2)