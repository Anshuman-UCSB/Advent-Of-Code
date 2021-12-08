from utils.aocUtils import *
from itertools import permutations
def main(input:str):
	p1 = 0
	p2 = 0
	nums = {v:k for k, v in zip(range(10),
			["abcefg","cf","acdeg","acdfg","bcdf","abdfg","abdefg","acf","abcdefg","abcdfg"])}
	for l in input.splitlines():
		lhs, rhs = map(lambda x: x.split(), l.split("|"))
		p1 += sum(len(w) in [2,3,4,7] for w in rhs)
		for p in permutations("abcdefg"):
			trans = str.maketrans("abcdefg", "".join(p))
			a = ["".join(sorted(w.translate(trans))) for w in lhs]
			if all(w in nums for w in a):
				b = ["".join(sorted(w.translate(trans))) for w in rhs]
				p2+=int("".join(str(nums[w]) for w in b))
	return (p1, p2)