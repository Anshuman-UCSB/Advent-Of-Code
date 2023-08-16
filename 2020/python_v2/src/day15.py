def main(input):
	nums = list(map(int, input.split(',')))
	seen = [0] * 30_000_000 # static sized array is faster than dictionary (4.9s vs 7.6s)
	for i,v in enumerate(nums):
		seen[v] = i+1
	n = nums[-1]
	for t in range(len(nums), 30_000_000):
		if seen[n] == 0:
			newn = 0
		else:
			newn = t-seen[n]
		seen[n] = t
		n = newn
		if t == 2019:
			p1 = n
	return p1, n

# wayyy too slow
# def main(input):
# 	nums = list(map(int, input.split(',')))
# 	seen = {}
# 	for i in range(len(nums)):
# 		seen[nums[i]] = [i+1]
# 	num = 0
# 	for t in range(len(nums)+1, 2020):
# 		old = num
# 		if old in seen:
# 			num = t - seen[old][-1]
# 			seen[old] = (seen[old]+[t])[-2:]
# 		else:
# 			num = 0
# 			seen[old] = [t]
# 	p1 = num
# 	for t in range(2020, 30000000):
# 		old = num
# 		if old in seen:
# 			num = t - seen[old][-1]
# 			seen[old] = (seen[old]+[t])[-2:]
# 		else:
# 			num = 0
# 			seen[old] = [t]
		
# 	return p1, num