from utils.aocUtils import *
from math import atan2
from collections import defaultdict

def getDeltas(asteroids, source):
	deltas = defaultdict(list)
	for a in asteroids:
		if a != source:
			deltas[-atan2(a[1]-source[1], a[0]-source[0])].append(a)
	return deltas

def main(input:str):
	asteroids = set()
	for y, row in enumerate(input.splitlines()):
		for x, v in enumerate(row):
			if v == '#':
				asteroids.add((x,y))
	p1 = 0
	maxPos = None
	maxDelta = None
	for a in asteroids:
		deltas = getDeltas(asteroids, a)
		if p1 < len(deltas):
			p1 = len(deltas)
			maxDelta = deltas
			maxPos = a
	order = list(maxDelta.keys())
	order.sort()
	order = order[::-1]
	start = atan2(1,0) # start straight up
	i = order.index(start)

	dist = lambda x: abs(x[1]-maxPos[1])+abs(x[0]-maxPos[0])

	for k in maxDelta.keys():
		maxDelta[k].sort(key=dist)

	popped = []
	while len(popped) < 200:
		if len(maxDelta[order[i]]) > 0:
			popped.append(maxDelta[order[i]].pop(0))
		i = (i+1)%len(maxDelta)
	p2 = popped[-1][0]*100+popped[-1][1]
	return (p1, p2)