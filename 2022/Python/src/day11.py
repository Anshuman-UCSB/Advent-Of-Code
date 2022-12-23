from utils.aocUtils import *
import math

def parseOperation(line):
	if line == "old * old":
		return lambda x: pow(x,2)
	nm = int(line.split()[2])
	if '+' in line:
		return lambda x: x+nm
	elif '*' in line:
		return lambda x: x*nm
lcm = 1
class Monkey:
	def __init__(self, inp):
		lines = inp.splitlines()
		nums = readNums(inp)
		self.name = nums[0]
		self.items = readNums(lines[1])
		self.const = nums[-4]
		self.opString = " ".join(lines[2].split()[-3:])
		self.operation = parseOperation(lines[2][19:])
		self.mod   = nums[-3]
		self.true  = nums[-2]
		self.false = nums[-1]

		self.p1 = 0
	def __str__(self):
		b = ""
		b+=f"Monkey {self.name}"
		b+=f"	if % {self.mod} then {self.true} else {self.false}"
		b+=f"	operation {self.opString}"
		b+=f"	inv {self.items}"
		return b
	def __repr__(self):
		return f"Monkey {self.name}: {self.items}"
	
	def inspect(self, p1):
		# print(self.name, "is inspecting", self.items)
		self.p1 += len(self.items)
		if p1:
			self.items = [self.operation(v)//3 for v in self.items]
		else:
			self.items = [self.operation(v)%lcm for v in self.items]
	def throw(self, monkeys):
		for i in self.items:
			if i%self.mod == 0:
				monkeys[self.true].items.append(i)
			else:
				monkeys[self.false].items.append(i)
		self.items = []

def round(monkeys, p1):
	for i in range(len(monkeys)):
		monkeys[i].inspect(p1)
		monkeys[i].throw(monkeys)
def printRound(round, monkeys):
	print("\nRound",round)
	for m in monkeys.values():
		print(f"Monkey {m.name}: {', '.join(map(str,m.items))}")
		
def main(input:str):
	global lcm
	p1 = p2 = 0
	monkeys1 = {}
	monkeys2 = {}
	for l in input.strip().split("\n\n"):
		m = Monkey(l)
		lcm*=m.mod
		monkeys1[m.name] = m
		monkeys2[m.name] = Monkey(l)
	ans = []
	for rounds, part in ((20, True), (10000, False)):
		monkeys = monkeys1 if part else monkeys2
		for rn in range(1,rounds+1):
			round(monkeys, part)
		inpsections = sorted([m.p1 for m in monkeys.values()])
		ans.append(inpsections[-1]*inpsections[-2])
	return ans