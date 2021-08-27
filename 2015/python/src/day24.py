from utils.aocUtils import readNums
from itertools import combinations
from functools import reduce
from operator import mul

def solve(nums, parts):
	targetWeight = sum(nums) // parts
	for n in range(1, len(nums)):
		good = [reduce(mul, x) for x in combinations(nums, n) if sum(x) == targetWeight]
		if good != []:
			return min(good)

def main(input:str):
	nums = readNums(input)
	return (solve(nums, 3),solve(nums, 4))