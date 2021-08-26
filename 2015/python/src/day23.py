from utils.aocUtils import readNums

class CPU:
	def __init__(self):
		self.regs = [0,0]
		self.pos = 0

	def step(self, instrs):
		opc, *args = instrs[self.pos]
		if opc == "hlf":
			self.regs[args[0]]//=2
		elif opc == "tpl":
			self.regs[args[0]]*=3
		elif opc == "inc":
			self.regs[args[0]]+=1
		elif opc == "jmp":
			self.pos += args[0]-1
		elif opc == "jie":
			if self.regs[args[0]]%2==0:
				self.pos += args[1]-1
		elif opc == "jio":
			if self.regs[args[0]]==1:
				self.pos += args[1]-1
		self.pos+=1
	
	def run(self, instrs):
		while 0<=self.pos<len(instrs):
			self.step(instrs)

def main(input:str) -> tuple:
	instrs = []
	for l in input.splitlines():
		spl = l.split()
		if len(spl) == 2:
			if spl[0] != "jmp":
				instrs.append((spl[0], 0 if spl[1] =='a' else 1))
			else:
				instrs.append((spl[0], int(spl[1])))
		else:
			instrs.append((spl[0], 0 if spl[1][0] =='a' else 1, int(spl[-1])))
	c = CPU()
	c.run(instrs)
	c2 = CPU()
	c2.regs[0] = 1
	c2.run(instrs)
	return (c.regs[1], c2.regs[1])