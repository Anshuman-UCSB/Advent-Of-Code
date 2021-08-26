from time import sleep
from copy import deepcopy
baseopc = {
	'c':1,
	'i':2,
	'd':3,
	'j':4,
	'p':5,
	'm':6,
	't':7,
	'u':8
}

class instr:
	def __init__(self, line):
		spl = line.split()
		self.opc = baseopc[line[0]]
		self.a = spl[1]
		self.argSize = 1
		if self.a not in "abcd":
			self.opc += 100
			self.a = int(self.a)
		if(len(spl)>2):
			self.argSize +=1
			self.b = spl[2]
			if self.b not in "abcd":
				self.opc += 1000
				self.b = int(self.b)

	def toggle(self):
		# print(self.opc, end=" -> ")
		if(self.opc in [5, 6]):
			raise(Exception("TRYING TO TOGGLE INVALID"))
		if self.argSize == 1:
			if self.opc%10 == 2:
				self.opc+=1
			else:
				self.opc+=2-self.opc%10
		else:
			if self.opc%10 == 4:
				self.opc-=3
			else:
				self.opc+=4-self.opc%10
		# print(self.opc)


	def exec(self, regs, instrs, pos, debug = False):
		newPos = 1
		if debug: print(pos,"	",self.opc,"	",end="")
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
		elif(self.opc == 104): 
			if(self.a!=0):
				newPos = regs[self.b]
		elif(self.opc == 2):
			regs[self.a]+=1
		elif(self.opc == 3):
			regs[self.a]-=1
		elif(self.opc == 6):
			regs[self.a]+=regs[self.b]
			regs[self.b] = 0
		elif(self.opc == 7):
			if 0<=pos+regs[self.a]<len(instrs):
				instrs[pos+regs[self.a]].toggle()
		elif(self.opc == 8):
			regs[self.a]*=regs[self.b]
			regs[self.b] = 0
		elif(self.opc == 1008):
			regs[self.a]*=self.b

		elif(self.opc == 105):
			pass
		else:
			raise(Exception("UNKNOWN OPC: "+str(self.opc)))
		if debug:
			print(regs)
		return newPos

def main(input:str) -> tuple:
	instrs = []
	for l in input.splitlines():
		instrs.append(instr(l))
	instrB = deepcopy(instrs)
	opcs = set([x.opc for x in instrs])
	# print(opcs)
	regs = {c:0 for c in "abcd"}
	regs['a'] = 7
	p = 0
	p1 = None
	try:
		while True:
			p+=instrs[p].exec(regs, instrs, p)
	except IndexError:
		p1 = regs['a']

	regs = {c:0 for c in "abcd"}
	regs['a'] = 12
	p = 0
	try:
		while True:
			p+=instrB[p].exec(regs, instrB, p)
	except IndexError:
		pass

	return (p1, regs['a'])
