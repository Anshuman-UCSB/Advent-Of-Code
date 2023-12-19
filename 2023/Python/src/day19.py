import re
from copy import deepcopy
class Part:
	def __init__(self, line):
		# self.data = {k:int(v) for k,v in re.findall(r"([xmas])=(-?\d+)",line)}
		self.x,self.m,self.a,self.s = map(int, re.findall(r"-?\d+",line))
		self.score = self.x+self.m+self.a+self.s
	def __repr__(self):
		return str((self.x, self.m, self.a, self.s))

class PartRange:
	def __init__(self, ranges=None):
		self.ranges = deepcopy(ranges) or {l:[0,4001] for l in "xmas"}
	def splitOn(self, lhs):
		inRange = PartRange(self.ranges)
		outRange = PartRange(self.ranges)
		assert lhs[1] in "<>", "Something wrong with LHS "+lhs
		num = int(lhs[2:])
		existingRange = inRange.ranges[lhs[0]]
		if existingRange[0] <= num <= existingRange[1]:
			if lhs[1] == '>':
				inRange.ranges[lhs[0]][0] = num
				outRange.ranges[lhs[0]][1] = num+1
			else:
				inRange.ranges[lhs[0]][1] = num
				outRange.ranges[lhs[0]][0] = num-1
		elif num < existingRange[0] and lhs[1] == '>':
			outRange=None
		elif num > existingRange[1] and lhs[1] == '<':
			outRange=None
		else:
			inRange=None
			outRange=None
		return inRange, outRange
	def score(self):
		ans = 1
		for l,h in self.ranges.values():
			ans*=(h-l-1)
		return ans
	def __repr__(self):
		return str(self.ranges)

def main(input):
	workflows_raw, parts_raw = input.split("\n\n")
	
	workflows = {}
	def testPart(part, name):
		if name in "AR":
			return name=="A"
		rules = workflows[name]
		for r in rules:
			if ":" not in r:
				return testPart(part, r)
			lhs,next = r.split(":")
			if eval(f"part.{lhs[0]}"+lhs[1:]):
				return testPart(part, next)
			

	for l in workflows_raw.splitlines():
		name, rules = l[:-1].split("{")
		workflows[name] = rules.split(",")		

		parts = [Part(l) for l in parts_raw.splitlines()]	
	# print(parts)
	validRanges = []
	def testRange(partRange, name,level=0):
		if partRange is None: return
		assert all(r[0]+1<r[1] for r in partRange.ranges.values()), "Recieving invalid range"
		print(" "*level,name, partRange)
		if name in "AR":
			if name == "A":
				validRanges.append(partRange)
		else:
			rules = workflows[name]
			for r in rules:
				if ":" not in r:
					testRange(partRange, r,level+1)
				else:
					lhs,next = r.split(":")
					inR, outR = partRange.splitOn(lhs)
					# print(inR, outR, lhs)
					testRange(inR, next,level+1)
					partRange = outR
					level+=1
					if partRange == None: return
	testRange(PartRange(), "in")	
	print(validRanges)
	# print(testPart(parts[0], "in"))
	p1 = 0
	for p in parts:
		p1 += p.score if testPart(p, "in") else 0
	return p1, sum(pr.score() for pr in validRanges)