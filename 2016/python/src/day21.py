from src.aocUtils import readNums
import numpy as np
from itertools import permutations

def p1(input, s):
	
	for l in input.splitlines():
		spl = l.split()
		nums = readNums(l)
		if l.startswith("swap position"):
			s[[nums[0], nums[1]]] = s[[nums[1], nums[0]]]
		elif l.startswith("swap letter"):
			a,b=np.where(np.logical_or(s == spl[2],s==spl[-1]))[0]
			s[[a, b]] = s[[b, a]]
		elif l.startswith("rotate based"):
			a=np.where(s == spl[-1])[0][0]
			if a>=4:
				a+=1
			s = np.roll(s, a+1)
		elif l.startswith("rotate"):
			a = int(spl[-2])
			if "left" in l:
				a *= -1
			s = np.roll(s, a)
		elif l.startswith("reverse"):
			s[nums[0]:nums[1]+1] = s[nums[0]:nums[1]+1][::-1]
		elif l.startswith("move"):
			pop = np.delete(s, nums[0])
			s = np.insert(pop, nums[1], s[nums[0]])
		# print("".join(s),"	",l)
	return "".join(s)

def main(input:str) -> tuple:
	for s in permutations("abcdefgh"):
		if(p1(input, s = np.array([x for x in s])) == "fbgdceah"):
			p2 = "".join(s)
			break
	return (p1(input, s = np.array([x for x in "abcdefgh"])), p2)