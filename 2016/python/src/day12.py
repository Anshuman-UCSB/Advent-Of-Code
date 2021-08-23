from time import sleep
baseopc = {
	'c':1,
	'i':2,
	'd':3,
	'j':4,
	'p':5,
	'm':6
}

class instr:
	def __init__(self, line):
		spl = line.split()
		self.opc = baseopc[line[0]]
		self.a = spl[1]
		if self.a not in "abcd":
			self.opc += 100
			self.a = int(self.a)
		if(len(spl)>2):
			self.b = spl[2]
			if self.b not in "abcd":
				self.opc += 1000
				self.b = int(self.b)

	def exec(self, regs):
		newPos = 1
		if(self.opc == 1):
			regs[self.b] = regs[self.a]
		elif(self.opc == 101): 
			regs[self.b] = self.a
		elif(self.opc == 1004): 
			if(regs[self.a]!=0):
				newPos = self.b
		elif(self.opc == 1104): 
			if(self.a!=0):
				newPos = self.b
		elif(self.opc == 2):
			regs[self.a]+=1
		elif(self.opc == 3):
			regs[self.a]-=1
		elif(self.opc == 6):
			regs[self.a]+=regs[self.b]
			regs[self.b] = 0
		elif(self.opc == 105):
			pass
		else:
			raise(Exception("UNKNOWN OPC: "+str(self.opc)))
		return newPos

def main(input:str) -> tuple:
	instrs = []
	for l in input.splitlines():
		instrs.append(instr(l))
	regs = {c:0 for c in "abcd"}
	p = 0
	p1 = None
	try:
		while True:
			p+=instrs[p].exec(regs)
			# print(p,"	",regs)
			# sleep(.1)
	except IndexError:
		p1 = regs['a']
	regs = {c:0 for c in "abcd"}
	regs['c'] = 1
	p = 0
	try:
		while True:
			p+=instrs[p].exec(regs)
			# print(p,"	",regs)
			# sleep(.1)
	except IndexError:
		pass

	return (p1, regs['a'])
