from utils.aocUtils import *
from itertools import permutations

def main(input:str):
	p1, p2 = 0, 0
	for lhs, rhs in [((spl:=x.split(" | "))[0].split(),spl[1].split())  for x in input.splitlines()]:
		knowns = {len(s):set(s) for s in lhs}
		n = 0
		for o in map(set, rhs):
			match len(o), len(o&knowns[4]), len(o&knowns[2]):
				case 2,_,_: n=n*10+1; p1+=1
				case 3,_,_: n=n*10+7; p1+=1
				case 4,_,_: n=n*10+4; p1+=1
				case 7,_,_: n=n*10+8; p1+=1
				case 5,2,_: n=n*10+2
				case 5,3,1: n=n*10+5
				case 5,3,2: n=n*10+3
				case 6,4,_: n=n*10+9
				case 6,3,1: n=n*10+6
				case 6,3,2: n=n*10+0
		p2+=n
	return (p1, p2)

# too slow lmao
def old(input:str):
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