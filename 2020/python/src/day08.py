from utils.aocUtils import *
class CPU:
	def __init__(self, input):
		self.acc = 0
		self.pos = 0
		self.visited = set()
		self.instrs = []
		for l in input:
			spl = l.split()
			spl[1] = int(spl[1])
			if spl[0] == "acc": spl[0] = self.add
			elif spl[0] == "jmp": spl[0] = self.jmp
			elif spl[0] == "nop": spl[0] = self.nop
			self.instrs.append(spl)
	def add(self, x): self.acc+=x; self.pos+=1
	def jmp(self, x): self.pos+=x
	def nop(self, x): self.pos+=1

	def p1(self):
		while True:
			if self.pos in self.visited:
				return self.acc
			self.visited.add(self.pos)
			cmd, param = self.instrs[self.pos]
			cmd(param)
	def p2(self):
		while True:
			if self.pos in self.visited:
				return False
			self.visited.add(self.pos)
			cmd, param = self.instrs[self.pos]
			# print("calling for",cmd)
			cmd(param)
			if self.pos == len(self.instrs):
				return self.acc

def main(input:str):
	lines = input.splitlines()
	c = CPU(lines)
	p1 = c.p1()
	for i,l in enumerate(lines):
		s = l.split()
		if s[0] == 'nop':
			c = lines.copy()
			c[i] = " ".join(("jmp", s[1]))
			p2 = CPU(c).p2()
			if p2:break
		elif s[0] == 'jmp':
			c = lines.copy()
			c[i] = " ".join(("nop", s[1]))
			p2 = CPU(c).p2()
			if p2:break
	return (p1, p2)