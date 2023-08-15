def main(input):
	nums = list(map(int, input.splitlines()))
	i = 24
	while True:
		i+=1
		valid = False
		for j in range(i-25,i):
			for k in range(j+1,i):
				if nums[j]+nums[k] == nums[i]:
					valid = True
					break
			if valid:
				break
		if not valid:
			p1 = nums[i]
			break
	l,r = 0,1
	rsum = nums[l]+nums[r]
	while rsum != p1:
		if rsum < p1:
			r+=1
			rsum+=nums[r]
		else:
			rsum-=nums[l]
			l+=1
	
	return p1, min(nums[l:r+1])+max(nums[l:r+1])