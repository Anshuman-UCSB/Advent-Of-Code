from utils.aocUtils import *
import statistics

@cache
def stepsum(n):
	return n*(1+n)//2

def main(input:str):
	nums = readNums(input)
	nums.sort()
	median, average = int(statistics.median(nums)), statistics.mean(nums)
	average = int(average) if average>median else int(average)+1
	p1 = sum(abs(x-median) for x in nums)
	p2 = sum(stepsum(abs(x-average)) for x in nums)
	return (p1, p2)