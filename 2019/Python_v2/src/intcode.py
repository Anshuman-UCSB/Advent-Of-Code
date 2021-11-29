class EmptyInput(Exception):
	pass
class StoppedCPU(Exception):
	pass
class InvalidWriteType(Exception):
	pass

class CPU:
	def __init__(self, inp):
		self.pc = 0
		self.rel = 0
		self.done = False
		self.regs = list(map(int,inp.split(',')))
		self.inputQ = []
		self.outputQ = []

	def extendRegs(self, size):
		if len(self.regs)<=size:
			self.regs.extend([0 for _ in range(len(self.regs), size+1)])

	def calcR(self, opc, pos):
		# print(opc, pos, opc//pow(10,pos+1)%10)
		return opc//pow(10,pos+1)%10

	def read(self, i, opc, pos):
		rtype = self.calcR(opc, pos)
		if rtype == 0:
			self.extendRegs(self.regs[i])
			return self.regs[self.regs[i]]
		if rtype == 1:
			self.extendRegs(i)
			return self.regs[i]
		if rtype == 2:
			self.extendRegs(self.regs[i]+self.rel)
			return self.regs[self.regs[i]+self.rel]

	def write(self, i, val, opc, pos):
		rtype = self.calcR(opc, pos)
		p = self.regs[i]
		if rtype == 0:
			self.extendRegs(p)
			self.regs[p] = val
			# print("[0] Wrote: ",self.regs[self.regs[i]], "to", self.regs[i])
		elif rtype == 2:
			self.extendRegs(p+self.rel)
			self.regs[p+self.rel] = val
			# print("[2] Wrote: ",self.regs[self.regs[i]+self.rel], "to", self.regs[i]+self.rel)
		else:
			raise InvalidWriteType

	def push(self, v):
		self.inputQ.append(v)
	def pop(self):
		return self.outputQ.pop(0)

	def cycle(self):
		opc = self.regs[self.pc]
		funcs = {
			1:self.opc1,
			2:self.opc2,
			3:self.opc3,
			4:self.opc4,
			5:self.opc5,
			6:self.opc6,
			7:self.opc7,
			8:self.opc8,
			9:self.opc9,
			99:self.opc99,
		}
		funcs[opc%100](opc)


	# ALU ops
	def opc1(self, opc):
		a,b = [self.read(self.pc+i, opc, i) for i in [1,2]]
		c = self.pc+3
		val = a + b
		self.write(c, val, opc, 3)
		self.pc+=4
	def opc2(self, opc):
		a,b = [self.read(self.pc+i, opc, i) for i in [1,2]]
		c = self.pc+3
		val = a * b
		self.write(c, val, opc, 3)
		self.pc+=4
	def opc7(self, opc):
		a,b = [self.read(self.pc+i, opc, i) for i in [1,2]]
		c = self.pc+3
		val = 1 if a < b else 0
		self.write(c, val, opc, 3)
		self.pc+=4
	def opc8(self, opc):
		a,b = [self.read(self.pc+i, opc, i) for i in [1,2]]
		c = self.pc+3
		val = 1 if a == b else 0
		self.write(c, val, opc, 3)
		self.pc+=4
	

	# I/O
	def opc3(self, opc):
		if len(self.inputQ)==0:
			raise(EmptyInput)
		self.write(self.pc+1, self.inputQ.pop(0), opc, 1)
		self.pc+=2
	def opc4(self, opc):
		a = self.read(self.pc+1, opc, 1)
		self.outputQ.append(a)
		self.pc+=2

	# jumps
	def opc5(self, opc):
		a,b = [self.read(self.pc+i, opc, i) for i in [1,2]]
		if a != 0:
			self.pc = b
		else:
			self.pc+=3
	def opc6(self, opc):
		a,b = [self.read(self.pc+i, opc, i) for i in [1,2]]
		if a == 0:
			self.pc = b
		else:
			self.pc+=3
	
	# rel pointer
	def opc9(self, opc):
		a = self.read(self.pc+1, opc, 1)
		self.rel+=a
		self.pc +=2

	# end
	def opc99(self, opc):
		self.done = True

	def run(self, debug = False):
		if self.done:
			raise StoppedCPU
		while not self.done:
			if debug:
				print("CYCLE")
				print("	",self.pc,self.rel,self.regs[self.pc:self.pc+4])
			self.cycle()
			if debug:
				print("	",self.outputQ)

	def runUntilInput(self, debug= False):
		try:
			self.run(debug)
		except EmptyInput:
			pass

def simulate(input, inpList = None, debug = False):
	c = CPU(input)
	if inpList != None:
		for i in inpList:
			c.push(i)
	c.run(debug)
	return c.outputQ