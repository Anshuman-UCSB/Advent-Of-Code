from utils.aocUtils import *
def main(input:str):
	nums = readNums(input)
	p1 = 0
	for i,n in enumerate(nums):
		if n>nums[i-1]:
			p1+=1
	sliding = [nums[n]+nums[n+1]+nums[n+2] for n in range(len(nums)-2)]
	p2 = 0
	for i,n in enumerate(sliding):
		if n>sliding[i-1]:
			p2+=1
	return (p1, p2)