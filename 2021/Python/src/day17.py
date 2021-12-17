from utils.aocUtils import *

def testVel(vel, nums):
	stVel = int(vel.imag)
	lx, hx, ly, hy = nums
	pos = 0
	while pos.real <= hx and pos.imag >= ly:
		pos+=vel
		vel-= 1j if vel.real<=0 else 1+1j
		if lx<=pos.real<=hx and ly<=pos.imag<=hy:
			return True, sum(range(1, stVel+1))
	return False, None

def main(input:str):
	p1 = 0
	p2 = 0
	nums = readNums(input)
	for x in range(nums[1]+1):
		for y in range(nums[2], -nums[2]):
			bl, ans = testVel(crd2im(x, y), nums)
			if bl:
				p1 = max(p1, ans)
				p2+=1
	return (p1, p2)