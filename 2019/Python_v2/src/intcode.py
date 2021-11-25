class CPU:
	def __init__(self, inp):
		self.pc = 0
		self.done = False
		self.regs = list(map(int,inp.split(',')))

	def extendRegs(self, size):
		if len(self.regs)<=size:
			self.regs.extend([0 for _ in range(len(self.regs), size+1)])

	def read(self, i):
		self.extendRegs(i)
		return self.regs[i]

	def write(self, i, val):
		self.extendRegs(i)
		self.regs[i] = val

	def cycle(self):
		self.extendRegs(self.pc)
		opc = self.regs[self.pc]
		if opc == 99:
			self.done = True
		elif opc == 1:
			a,b,c = self.regs[self.pc+1:self.pc+4]
			self.write(c, self.read(a)+self.read(b))
			self.pc+=4
		elif opc == 2:
			a,b,c = self.regs[self.pc+1:self.pc+4]
			self.write(c, self.read(a)*self.read(b))
			self.pc+=4

	def run(self):
		while not self.done:
			self.cycle()