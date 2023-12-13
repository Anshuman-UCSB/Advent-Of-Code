try:
	from functools import cache
except ImportError:
	from functools import lru_cache
	cache = lru_cache(maxsize=None)
import re

	
def solve(line):
	print(line)
	@cache
	def dp(line, pos, nums, groups):
		...
	return 0

def parseLine(l):
	lhs,rhs = re.sub(r"\.+",".",l).split()
	nums = eval(rhs)
	return (lhs+".", nums) # Adding . at end to avoid out of bounds

def main(input):
	inps = [parseLine(l) for l in input.splitlines()]
	return sum(solve(l) for l in inps), None