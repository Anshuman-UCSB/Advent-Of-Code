def main(input):
	nums = sorted(list(map(int, input.splitlines())))
	counter = [0,0,0,1]
	counter[nums[0]]+=1
	for i in range(len(nums)-1):
		counter[nums[i+1]-nums[i]]+=1
	dp = {n:0 for n in nums}
	dp[0]=1
	for n in [0]+nums:
		for d in range(1,4):
			if n+d in dp:
				dp[n+d]+=dp[n]
	return counter[1]*counter[3], dp[nums[-1]]