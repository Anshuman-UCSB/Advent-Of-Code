from utils.aocUtils import readNums

class CPU:
	def __init__(self, regs):
		if isinstance(regs, str):
			self.regs = readNums(regs)
		else:
			self.regs = regs.copy()
		self.pos = 0
		self.rel = 0
		self.done = False

	def step(self):
		opc, a, b, c = self.regs[self.pos:self.pos+4]
		if opc == 1: 	self.regs[c] = self.regs[a] + self.regs[b]	; self.pos += 4
		elif opc == 2: 	self.regs[c] = self.regs[a] * self.regs[b]	; self.pos += 4
		elif opc == 99: self.done = True

	def run(self):
		while not self.done:
			self.step()