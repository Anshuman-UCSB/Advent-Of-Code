from utils.aocUtils import *
import re
import numpy as np

def main(input:str):
	TEST = False
	y = 10 if TEST else 2_000_000

	p1 = p2 = 0
	nums = list(map(int, re.findall(r'-?\d+', input)))
	pairs = [nums[i:i+4] for i in range(0,len(nums),4)]

	blocked = set()
	inf = float('inf')
	p1range = [inf, -inf]
	lines = [[],[]]
	for sx, sy, bx, by in pairs:
		dist = abs(bx-sx)+abs(by-sy)
		lines[0].append(sy-sx)
		lines[1].append(sy+sx)
		if sy == y: blocked.add(sx)
		if by == y: blocked.add(bx)
		wiggle = dist - abs(y-sy)
		if wiggle >= 0:
			p1range[0] = min(p1range[0], sx-wiggle)
			p1range[1] = max(p1range[1], sx+wiggle)
	# print(pos1_lines)
	# print(neg1_lines)
	p1 += p1range[1] - p1range[0] + 1 
	p1 -= sum(1 for v in blocked if p1range[0]<=v<=p1range[1])
	return (p1, p2)