from utils.aocUtils import *
from math import atan2, pi
from collections import defaultdict

def getDiff(a, b):
	return (b[0]-a[0], -b[1]+a[1])

def main(input:str):
	s = input.splitlines()
	points = set()
	for y in range(len(s)):
		for x in range(len(s[0])):
			if s[y][x] == '#':
				points.add((x,y))
	
	p1 = 0
	pos = None
	for p in points:
		t = set()
		for p2 in points:
			if p2 == p:	continue
			x, y = getDiff(p, p2)
			t.add(atan2(y,x))
		if len(t)>p1:
			p1 = len(t)
			pos = p
	m = defaultdict(list)
	for p in points:
		if p != pos:
			x, y = getDiff(pos, p)
			m[atan2(y,x)].append(p)
	for v in m.values():
		v.sort(key=lambda x: sum(map(abs, getDiff(pos, x))))
	keys = list(m.keys())
	keys.sort(lambda x: ((pi/2)-x)%(2*pi))
	popped = 0
	i = 0
	while popped<200:
		if m[keys[i]] != []:
			popped +=1
			p2 = m[keys[i]].pop(0)
		i = (i+1)%len(keys)
	p2 = p2[0]*100+p2[1]
	return (p1, p2)