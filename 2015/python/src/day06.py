import numpy as np
from utils.aocUtils import readNums
def main(input:str) -> tuple:
	grid = np.zeros((1000,1000))
	grid2 = np.zeros((1000,1000))
	for l in input.splitlines():
		nums = readNums(l)
		if "on" in l:
			grid[nums[1]:1+nums[3], nums[0]:1+nums[2]]=1
			grid2[nums[1]:1+nums[3], nums[0]:1+nums[2]]+=1
		elif "off" in l:
			grid[nums[1]:1+nums[3], nums[0]:1+nums[2]]=0
			grid2[nums[1]:1+nums[3], nums[0]:1+nums[2]]-=1
			grid2[grid2<0]+=1
		elif "toggle" in l:
			grid[nums[1]:1+nums[3], nums[0]:1+nums[2]]=1-grid[nums[1]:1+nums[3], nums[0]:1+nums[2]]
			grid2[nums[1]:1+nums[3], nums[0]:1+nums[2]]+=2
	# print(grid)
		
	return (int(np.sum(grid)), int(np.sum(grid2)))