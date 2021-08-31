from utils.aocUtils import *
import re
from copy import deepcopy

def isInRanges(n, ranges):
	for low, high in ranges:
		if low<=n<=high:
			return False
	return True

class rule:
	def __init__(self, line):
		self.name = line.split(":")[0]
		self.ranges = []
		for match in re.findall(r"(\d+)-(\d+)", line):
			self.ranges.append((int(match[0]), int(match[1])))

	def inRange(self, num):
		for low, high in self.ranges:
			if low<=num<=high:
				return True
		return False

def p1s(input):
	rules, ticket, tickets = input.split("\n\n")
	ranges = []
	for l in rules.splitlines():
		for match in re.findall(r"(\d+)-(\d+)", l):
			ranges.append((int(match[0]), int(match[1])))
	out = 0
	invalid = set()
	for t in tickets.splitlines():
		nums = readNums(t)
		for n in nums:
			if isInRanges(n, ranges):
				# print(n)
				invalid.add(t)
				out+=n
	tickets = [x for x in tickets.splitlines()[1:] if x not in invalid]
	return (out, tickets)

def p2s(input, tickets):
	rules = [rule(x) for x in input.split("\n\n")[0].splitlines()]
	possibles = [deepcopy(rules) for _ in range(20)]
	for ticket in tickets:
		nums = readNums(ticket)
		for i in range(20):
			n = nums[i]
			for j in range(len(possibles[i])-1, -1, -1):
				if not possibles[i][j].inRange(n):
					del possibles[i][j]
	m = {}
	while len(m) < 20:
		for i,p in enumerate(possibles):
			if len(p) == 1:
				m[p[0].name] = i
				for j, t in enumerate(possibles):
					possibles[j] = list(filter(lambda x: x.name != p[0].name, t))
	
	myTicket = readNums(input.split("\n\n")[1].splitlines()[1])
	out = 1
	for k, v in m.items():
		if "departure" in k:
			out *= myTicket[v]
	return out
		

def main(input:str):
	p1, tickets = p1s(input)
	p2 = p2s(input, tickets)
	return (p1, p2)