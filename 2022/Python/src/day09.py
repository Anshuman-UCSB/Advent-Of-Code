from utils.aocUtils import *
import numpy as np
from collections import defaultdict

def norm(vec):
	return vec/sum(abs(vec))

def update(head, tail):
	if max(abs(head-tail)) <= 1:
		return tail
	dir = head-tail
	if any(head == tail):
		return tail + norm(dir)
	else:
		if all(dir>0): 	# move top right
			return tail + 1
		if all(dir<0): 	# move bottom left
			return tail - 1
		if dir[0]>0:	# move bottom right
			return tail + np.array([1,-1])
		else:			# move bottom right
			return tail + np.array([-1,1])
	return None

def main(input:str):
	p1 = p2 = 0
	head, tail = np.zeros(2, dtype = int),np.zeros(2, dtype = int)
	directions = [np.array(dir) for dir in ([(0,1), (1,0), (0,-1), (-1,0)])]
	mapping = dict(zip("URDL", directions))
	nodes = [np.zeros(2, dtype=int) for _ in range(10)]
	tailPos2 = defaultdict(int)
	tailPos9 = defaultdict(int)
	for l in input.splitlines():
		dir, count = l.split()
		for _ in range(int(count)):
			nodes[0] += mapping[dir]
			for i in range(9):
				nodes[i+1] = update(nodes[i], nodes[i+1])
			tailPos2[tuple(nodes[1])]+=1
			tailPos9[tuple(nodes[9])]+=1
	return (len(tailPos2), len(tailPos9))