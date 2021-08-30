from utils.aocUtils import *
from itertools import groupby

tribbonaci = [1,1,2,4,7,13,24]

def main(input:str):
	nums = readNums(input)
	nums.append(0)
	nums.sort()
	d = deltas(nums)
	p2 = 1
	for key, group in groupby(d):
		if key == 1:
			p2*=tribbonaci[len(list(group))]
	p1 = d.count(1)*(d.count(3)+1)
	return (p1, p2)