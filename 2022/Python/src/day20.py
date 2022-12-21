from utils.aocUtils import *

def main(input:str):
	p1 = p2 = 0
	nums = []
	
	for id,l in enumerate(input.splitlines()):
		nums.append((int(l),id))
	def getInd(id):
		for ind, val in enumerate(nums):
			if val[1] == id:
				return ind
		return -1
	def findZero():
		for ind, val in enumerate(nums):
			if val[0] == 0:
				return ind
		return -1
	for id in range(len(nums)):
		pos = getInd(id)
		v = nums.pop(pos)
		pos = (pos+v[0])%len(nums)
		nums.insert(pos, v)
	print([v[0] for v in nums])
	zero_ind = findZero()
	for di in range(1000,4000,1000):
		print(p1, zero_ind, di)
		p1+=nums[(zero_ind+di)%len(nums)][0]
	return (p1, p2)