class CPU:
	def __init__(self, inp):
		self.pc = 0
		self.done = False
		self.regs = list(map(int,inp.split(',')))
		self.inputQ = []
		self.outputQ = []

	def extendRegs(self, size):
		if len(self.regs)<=size:
			self.regs.extend([0 for _ in range(len(self.regs), size+1)])

	def read(self, i, rtype = 0):
		if rtype == 1:
			return i
		if rtype == 0:
			self.extendRegs(i)
			return self.regs[i]

	def write(self, i, val):
		self.extendRegs(i)
		self.regs[i] = val

	def push(self, v):
		self.inputQ.append(v)

	def cycle(self):
		opc = self.read(self.pc)
		funcs = {
			1:self.opc1,
			2:self.opc2,
			3:self.opc3,
			4:self.opc4,
			5:self.opc5,
			6:self.opc6,
			7:self.opc7,
			8:self.opc8,
			99:self.opc99,
		}
		funcs[opc%100](opc)

	# ALU ops
	def opc1(self, opc):
		a,b,c = self.regs[self.pc+1:self.pc+4]
		self.write(c, self.read(a, opc//100%10)+self.read(b,opc//1000%10))
		self.pc+=4
	def opc2(self, opc):
		a,b,c = self.regs[self.pc+1:self.pc+4]
		self.write(c, self.read(a, opc//100%10)*self.read(b, opc//1000%10))
		self.pc+=4
	def opc7(self, opc):
		a,b,c = self.regs[self.pc+1:self.pc+4]
		self.write(c, 1 if self.read(a, opc//100%10)<self.read(b, opc//1000%10) else 0)
		self.pc+=4
	def opc8(self, opc):
		a,b,c = self.regs[self.pc+1:self.pc+4]
		self.write(c, 1 if self.read(a, opc//100%10)==self.read(b, opc//1000%10) else 0)
		self.pc+=4
	

	# I/O
	def opc3(self, opc):
		a = self.read(self.pc+1, opc//100%10)
		self.write(a, self.inputQ.pop(-1))
		self.pc+=2
	def opc4(self, opc):
		a = self.read(self.pc+1, opc//100%10)
		self.outputQ.append(self.read(a))
		self.pc+=2

	# jumps
	def opc5(self, opc):
		a, b = self.regs[self.pc+1:self.pc+3]
		a = self.read(a, opc//100%10)
		b = self.read(b, opc//1000%10)
		if a != 0:
			self.pc = b
		else:
			self.pc+=3
	def opc6(self, opc):
		a, b = self.regs[self.pc+1:self.pc+3]
		a = self.read(a, opc//100%10)
		b = self.read(b, opc//1000%10)
		if a == 0:
			self.pc = b
		else:
			self.pc+=3
	
	# end
	def opc99(self, opc):
		self.done = True

	def run(self, debug = False):
		while not self.done:
			if debug:
				print("CYCLE")
				print("	",self.pc,self.regs[self.pc:self.pc+4])
			self.cycle()
			if debug:
				print("	",self.outputQ)