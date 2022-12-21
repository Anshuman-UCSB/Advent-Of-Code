from utils.aocUtils import *
import numpy as np
import re

def parse(line):
	n, *nums = list(map(int,re.findall("\d+",line)))
	costs = np.zeros((4,4),dtype=int)
	costs[0,0] = nums[0]
	costs[1,0] = nums[1]
	costs[2,0:2] = nums[2:4]
	costs[3,0], costs[3,2] = nums[4], nums[5]
	return costs

def main(input:str):
	p1,p2 = 0,1
	o = [ sum(range(n)) for n in range(35) ]
	bps = list(map(parse, input.splitlines()))
	for n, costs in enumerate(bps):
		maximal = np.amax(costs, 0)
		def dfs( t , rb, best,
				inv,
				rbs ):
			if (rb < 3 and rbs[rb]>=maximal[rb]
				or inv[3] + rbs[3] * t + o[ t ] <= best[0]):
				return 
			while t:
				if all(inv >= costs[rb]):
					built = np.zeros(4, dtype=int)
					built[rb] += 1
					for g in range(4):
						dfs(t-1, g, best, inv - costs[rb] + rbs, rbs + built)
					return
				t -= 1
				inv += rbs
			best[0] = max(best[0], inv[3])
		best = [0]
		for g in range( 4 ):
			dfs( 24, g, best, np.zeros(4, dtype=int), np.array([1,0,0,0]))
		p1 += best[0] * (n+1)
		if n < 3:
			best = [0]
			for g in range( 4 ):
				dfs( 32, g, best, np.zeros(4, dtype=int), np.array([1,0,0,0]))
			p2*=best[0]
	return (p1, p2)