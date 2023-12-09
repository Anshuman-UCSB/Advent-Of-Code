def solve(nums):
	if len(set(nums)) == 1:
		return nums[0]
	diff = []
	for i in range(len(nums)-1):
		diff.append(nums[i+1]-nums[i])
	return nums[-1] + solve(diff)

def main(input):
	inpNums = [list(map(int, l.split())) for l in input.splitlines()]
	return sum(solve(n) for n in inpNums), sum(solve(n[::-1]) for n in inpNums)