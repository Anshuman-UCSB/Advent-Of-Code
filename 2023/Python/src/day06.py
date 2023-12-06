import math
import re
# time 7, dist 9
# x - how long we charge our boat up for (also its speed)
# (7-x)x = 9
# (t-x)x = d
# -x^2 + xt = d
# 0 = x^2 - tx + d
def findMargin(t, d):
	d += 1e-6 # magic
	low = int((t - math.sqrt(t**2 - 4*d))/2)
	high= int((t + math.sqrt(t**2 - 4*d))/2)
	return high - low

def solve(input):
	nums = list(map(int, re.findall(r"\d+", input)))
	num_races = len(nums)//2
	ans = 1
	for i in range(num_races):
		ans*=findMargin(nums[i], nums[i+num_races])
	return ans
	
def main(input):
	return solve(input), solve(input.replace(" ",""))