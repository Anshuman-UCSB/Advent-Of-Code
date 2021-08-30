from utils.aocUtils import *
from time import sleep

def main(input:str):
	nums = readNums(input)
	cache = {}
	last = -1
	for i in range(30000000):
		if i < len(nums):
			last = nums[i]
			cache[last] = i
		else:
			if last in cache:
				# print(cache)
				t = i-cache[last]-1
				cache[last] = i-1
				last = t
			else:
				cache[last] = i-1
				last = 0
		if i == 2020-1:
			p1 = last
	return (p1, last)

#0, 3, 6
#0, 3, 6, 0, 3, 3, 1, 0, 4, 0