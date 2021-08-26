from src.aocUtils import readNums
import pprint
import numpy as np

def main(input:str) -> tuple:
	nodes = {}
	pp = pprint.PrettyPrinter(indent = 4)
	for l in input.splitlines()[2:]:
		nums = readNums(l)
		nodes[tuple(nums[0:2])] = nums[2:]
	# pp.pprint(nodes)
	# Filesystem              Size  Used  Avail  Use%
	# /dev/grid/node-x0-y5     92T   73T    19T   79%
	p1 = 0
	left = 999
	for a, v1 in nodes.items():
		if v1[0]>100:
			left = min(left, a[0])
		elif v1[1]==0:
			start = a
		for b, v2 in nodes.items():
			if a == b:
				continue
			if v1[1] != 0 and v2[2]>v1[1]:
				p1+=1
	p2 = start[0]-left+1  + start[1] + (31-left) + 5*30 + 4

	
	return (p1, p2)
