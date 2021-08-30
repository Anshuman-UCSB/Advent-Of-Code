from utils.aocUtils import *
PREAMBLE_SIZE = 25

def sumsTo(nums, target):
	for i in range(len(nums)-1):
		for j in range(i+1, len(nums)):
			if nums[i] + nums[j] == target:
				return True
def p1s(nums):
	for i in range(PREAMBLE_SIZE,len(nums)):
		if not sumsTo(nums[i-PREAMBLE_SIZE:i], nums[i]):
			return nums[i]

def p2s(nums, target):
	l, h = 0, 1
	while True:
		s = sum(nums[l:h])
		if s == target:
			return max(nums[l:h]) + min(nums[l:h])
		elif s < target:
			h+=1
		else:
			l+=1

def main(input:str):
	nums = readNums(input)
	p1 = p1s(nums)
	p2 = p2s(nums, p1)
	return (p1, p2)