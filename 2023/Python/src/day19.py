import re
from copy import copy
class Part:
	def __init__(self, line):
		# self.data = {k:int(v) for k,v in re.findall(r"([xmas])=(-?\d+)",line)}
		self.x,self.m,self.a,self.s = map(int, re.findall(r"-?\d+",line))
		self.score = self.x+self.m+self.a+self.s
	def __repr__(self):
		return str((self.x, self.m, self.a, self.s))

class PartRange:
	def __init__(self, ranges=None):
		self.ranges = copy(ranges) or {l:[0,4001] for l in "xmas"}
	def splitOn(self, lhs):
		inRange = PartRange(self.ranges)
		outRange = PartRange(self.ranges)
		assert lhs[1] in "<>", "Something wrong with LHS "+lhs
		num = int(lhs[2:])
		existingRange = inRange.ranges[lhs[0]]
		if existingRange[0] <= num <= existingRange[1]:
			inRange.ranges[lhs[0]][1] = num
			outRange.ranges[lhs[0]][0] = num
			if lhs[1] == '>':
				inRange, outRange = outRange, inRange
		elif num < existingRange and lhs[1] == '>':
			outRange=None
		elif num > existingRange and lhs[1] == '<':
			outRange=None
		else:
			inRange=None
			outRange=None
		return inRange, outRange
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
			p2 = PartRange()
			print(p2.splitOn(lhs))
			

	for l in workflows_raw.splitlines():
		name, rules = l[:-1].split("{")
		workflows[name] = rules.split(",")		

		parts = [Part(l) for l in parts_raw.splitlines()]	
	# print(parts)

	# print(testPart(parts[0], "in"))
	p1 = 0
	for p in parts:
		p1 += p.score if testPart(p, "in") else 0
	return p1, None