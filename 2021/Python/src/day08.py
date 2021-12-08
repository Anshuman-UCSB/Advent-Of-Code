from utils.aocUtils import *
from itertools import permutations

def sortWord(w, mapping):
	return "".join(sorted([mapping[x] for x in w]))

def findMapping(allw, nums):
	for p in permutations(list("abcdefg")):
		ans = True
		testmap = {x:y for x,y in zip(p, "abcdefg")}
		for w in allw:
			s = sortWord(w, testmap)
			if s not in nums:
				ans = False
				break
		if ans:
			return {x:y for x,y in testmap.items()}

def getTranslation(mapping, nums):
	return {"".join(sorted(mapping[x] for x in w)):v for w,v in nums.items()}

def main(input:str):
	nums = {
		"abcefg":0,	"cf":1,		"acdeg":2,
		"acdfg":3,	"bcdf":4,	"abdfg":5,
		"abdefg":6,"acf":7,	"abcdefg":8,
		"abcdfg":9
	}
	p1 = 0
	p2 = 0
	for l in input.splitlines():
		p1+=sum([1 for w in l.split("|")[1].split() if len(w) in [2,4,3,7]])
		w = l.split("|")[0].split()
		mapping = findMapping(w, nums)
		translation = getTranslation(mapping, nums)
		n = 0
		for w in l.split("|")[1].split():
			n = n*10+nums["".join(sorted([mapping[c] for c in w]))]
		p2+=n
	
	return (p1, p2)