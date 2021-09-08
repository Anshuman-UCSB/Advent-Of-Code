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

	def step(self):
		try:
			opc = self.regs[self.pos]
			a = self.regs[self.pos+1]
			b = self.regs[self.pos+2]
			c = self.regs[self.pos+3]
		except IndexError:
			pass
		if opc ==     1:self.regs[c] = self.regs[a] + self.regs[b]	; self.pos += 4
		elif opc == 101:self.regs[c] = a + self.regs[b]				; self.pos += 4
		elif opc ==1001:self.regs[c] = b + self.regs[a]				; self.pos += 4
		elif opc ==1101:self.regs[c] = b + a						; self.pos += 4
		elif opc ==   2:self.regs[c] = self.regs[a] * self.regs[b]	; self.pos += 4
		elif opc == 102:self.regs[c] = a * self.regs[b]				; self.pos += 4
		elif opc ==1002:self.regs[c] = b * self.regs[a]				; self.pos += 4
		elif opc ==1102:self.regs[c] = b * a						; self.pos += 4

		elif opc == 3: 	
			if self.inputs != []:
				self.regs[a] = self.inputs.pop(0)
				self.pos += 2
			else:
				raise EmptyInput
		elif opc == 4: 	self.outputs.append(self.regs[a])			; self.pos += 2
		elif opc == 104:self.outputs.append(a)						; self.pos += 2

		elif opc ==   5:	self.pos = self.regs[b] if self.regs[a]!=0 else self.pos+3
		elif opc == 105:	self.pos = self.regs[b] if 			 a !=0 else self.pos+3
		elif opc ==1005:    self.pos = 			 b  if self.regs[a]!=0 else self.pos+3
		elif opc ==1105:	self.pos = 			 b  if           a !=0 else self.pos+3

		elif opc ==   6:	self.pos = self.regs[b] if self.regs[a]==0 else self.pos+3
		elif opc == 106:	self.pos = self.regs[b] if 			 a ==0 else self.pos+3
		elif opc ==1006:	self.pos = 			 b  if self.regs[a]==0 else self.pos+3
		elif opc ==1106:	self.pos = 			 b  if           a ==0 else self.pos+3

		elif opc ==   7:	self.regs[c] =  1 if self.regs[a] < self.regs[b] else 0		; self.pos += 4
		elif opc == 107:	self.regs[c] =  1 if           a  < self.regs[b] else 0		; self.pos += 4
		elif opc ==1007:	self.regs[c] =  1 if self.regs[a] <           b 	else 0	; self.pos += 4
		elif opc ==1107:	self.regs[c] =  1 if           a  <           b 	else 0	; self.pos += 4

		elif opc ==   8:	self.regs[c] =  1 if self.regs[a] ==self.regs[b] else 0		; self.pos += 4
		elif opc == 108:	self.regs[c] =  1 if           a  ==self.regs[b] else 0		; self.pos += 4
		elif opc ==1008:	self.regs[c] =  1 if self.regs[a] ==          b  else 0		; self.pos += 4
		elif opc ==1108:	self.regs[c] =  1 if           a  ==          b  else 0		; self.pos += 4

		elif opc == 99: self.done = True

	def run(self):
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