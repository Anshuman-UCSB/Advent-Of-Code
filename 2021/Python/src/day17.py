from utils.aocUtils import *

def testVel(vel, nums):
	lx, hx, ly, hy = nums
	pos = 0
	while pos.real <= hx and pos.imag >= ly:
		pos+=vel
		vel-= 1j if vel.real<=0 else 1+1j
		if lx<=pos.real<=hx and ly<=pos.imag<=hy:
			return True
	return False

def main(input:str):
	p2 = 0
	nums = readNums(input)
	p1 = ((nums[2])*(nums[2]+1))//2
	for x in range(nums[1]+1):
		for y in range(nums[2], -nums[2]):
			if testVel(crd2im(x, y), nums):
				p2+=1
	return (p1, p2)