from utils.aocUtils import readNums

class EmptyInput(Exception): pass

class CPU:
	def __init__(self, regs):
		if isinstance(regs, str):
			self.regs = readNums(regs)
		else:
			self.regs = regs.copy()
		self.pos = 0
		self.rel = 0
		self.inputs = []
		self.outputs = []
		self.done = False

	def push(self, n):
		self.inputs.append(n)
	def pop(self):
		return self.outputs.pop(0)

	def get(self, a):
		# print(a)
		v, mode = a
		if mode == 1:
			return v
		elif mode == 0:
			if v >= len(self.regs):
				self.regs = self.regs+[0]*(v-len(self.regs)+1)
			return self.regs[v]
		elif mode == 2:
			if v+self.rel >= len(self.regs):
				self.regs = self.regs+[0]*(v+self.rel-len(self.regs)+1)
			return self.regs[v+self.rel]
	def set(self, a, val):
		v, mode = a
		if mode == 1:
			raise("Tried to set with immediate mode")
		elif mode == 0:
			if v >= len(self.regs):
				self.regs = self.regs+[0]*(v-len(self.regs)+1)
			self.regs[v] = val
		elif mode == 2:
			if v+self.rel >= len(self.regs):
				self.regs = self.regs+[0]*(v+self.rel-len(self.regs)+1)
			self.regs[v+self.rel] = val
		
	def step(self):
		# print(self)
		try:
			opc = self.regs[self.pos]
			modes = []
			t = opc
			opc%=100
			t//=100
			for _ in range(3):
				modes.append(t%10)
				t//=10
			a = (self.regs[self.pos+1], modes[0])
			b = (self.regs[self.pos+2], modes[1])
			c = (self.regs[self.pos+3], modes[2])
		except IndexError:
			pass
		# print(modes, opc)
		if opc == 1:	self.set(c, self.get(a) + self.get(b)); self.pos += 4
		if opc == 2:	self.set(c, self.get(a) * self.get(b)); self.pos += 4
		elif opc == 3: 	
			if self.inputs != []:
				self.set(a, self.inputs.pop(0))
				self.pos += 2
			else:
				raise EmptyInput
		elif opc == 4: 	self.outputs.append(self.get(a))			; self.pos += 2

		elif opc == 5:	self.pos = self.get(b) if self.get(a)!=0 else self.pos+3
		elif opc == 6:	self.pos = self.get(b) if self.get(a)==0 else self.pos+3
		elif opc == 7:	self.set(c, 1 if self.get(a) < self.get(b) else 0)		; self.pos += 4
		elif opc == 8:	self.set(c, 1 if self.get(a) ==self.get(b) else 0)		; self.pos += 4
		elif opc == 9:	self.rel+=self.get(a)									; self.pos += 2

		elif opc == 99: self.done = True

	def run(self, waitInput = False):
		if waitInput:
			try:
				self.run()
			except EmptyInput:
				return
		while not self.done:
			self.step()

	def __str__(self):
		return f"""CPU:
	current regs: {self.regs[self.pos:self.pos+4]}
	pos: {self.pos}
	rel: {self.rel}
	inputs: {self.inputs}
	outputs: {self.outputs}
		"""