from utils.aocUtils import *
import re

def manhattan(x1, y1, x2, y2):
	return abs(x1-x2)+abs(y1-y2)
def posLine(sensor):
	return (sensor[0]+sensor[1]+sensor[2]+1, sensor[0]+sensor[1]-sensor[2]-1)
def negLine(sensor):
	return (sensor[0]-sensor[1]+sensor[2]+1, sensor[0]-sensor[1]-sensor[2]-1)
def Line(sensor, isPos):
	return posLine(sensor) if isPos else negLine(sensor)
def intersect(pos,neg):
	return (x:=((pos+neg)//2), pos-x)
def isAnswer(x,y, sensors):
	return (
		0<=x<=4_000_000 and 
		0<=y<=4_000_000 and 
		all(manhattan(sx, sy, x, y) > dist for sx,sy,dist in sensors)
	)

def p2solve(sensors):
	for s1 in sensors:
		for s2 in sensors:
			for dir in (True, False):
				for l1 in Line(s1, dir):
					for l2 in Line(s2, not dir):
						p = intersect(l1, l2)
						if isAnswer(*p, sensors):
							return p[0]*4_000_000 + p[1]

def main(input:str):
	y = 2_000_000
	p1 = 0
	
	nums = list(map(int, re.findall(r'-?\d+', input)))
	pairs = [nums[i:i+4] for i in range(0,len(nums),4)]

	blocked = set()
	inf = float('inf')
	p1range = [inf, -inf]
	sensors = []
	for sx, sy, bx, by in pairs:
		dist = manhattan(sx,sy, bx,by)
		sensors.append((sx,sy,dist))
		if sy == y: blocked.add(sx)
		if by == y: blocked.add(bx)
		wiggle = dist - abs(y-sy)
		if wiggle >= 0:
			p1range[0] = min(p1range[0], sx-wiggle)
			p1range[1] = max(p1range[1], sx+wiggle)

	p1 += p1range[1] - p1range[0] + 1 
	p1 -= sum(1 for v in blocked if p1range[0]<=v<=p1range[1])
	return (p1, p2solve(sensors))