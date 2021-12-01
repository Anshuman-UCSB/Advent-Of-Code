from utils.aocUtils import *

def getPattern(num):
	t = [0]*num+[1]*num+[0]*num+[-1]*num
	return t

def iter(nums):
	out= []
	for i in range(len(nums)):
		pattern = getPattern(i+1)
		out.append(0)
		for j, v in enumerate(nums):
			out[-1]+=v*pattern[(j+1)%len(pattern)]
	return [abs(x)%10 for x in out]

def iter2(nums):
	for i in range(len(nums)-2, -1, -1):
		nums[i] += nums[i+1]
		nums[i] %= 10
	return nums

def p1(input):
	nums = [int(x) for x in input.strip()]
	for x in range(100):
		nums = iter(nums)
	return "".join(map(str,nums[:8]))

def p2(input):
	nums = [int(x) for x in input.strip()]*10000
	offset = int(input[:7])
	nums = nums[offset:]
	for _ in range(100):
		nums = iter2(nums)
	return "".join(map(str,nums))

def main(input:str):
	# print(getPattern(4))
	return (p1(input)[:8], p2(input)[:8])