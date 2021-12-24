from time import sleep
from utils.aocUtils import *

class ALU:
	def __init__(self):
		self.vars = {l:0 for l in "xyzw"}
		self.args = []
		self.inputQ = []
		self.pos = 0

	def parse(self, inp):
		for l in inp.splitlines():
			spl = l.split()
			self.args.append(spl)
	
	def read(self, v):
		if v in self.vars:
			return self.vars[v]
		else: return int(v)

	def run(self):
		for l in self.args:
			self.step(l)
	def step(self, arg):
		opc, *args = arg
		match opc:
			case "inp": self.vars[args[0]] = int(self.inputQ.pop(0));print(self.vars)
			case "add": self.vars[args[0]]+=self.read(args[1])
			case "mul": self.vars[args[0]]*=self.read(args[1])
			case "div": self.vars[args[0]]//=self.read(args[1])
			case "mod": self.vars[args[0]]%=self.read(args[1])
			case "eql": self.vars[args[0]]=1 if (self.vars[args[0]]==self.read(args[1])) else 0
			case _: print(opc)

def testNum(n):
	n = [int(x) for x in str(n)]
	z =x = 0
	for d, n0, n1, n2 in zip(n,[1,1,1,1,1,26,1,26,26,1,26,26,26,26],
			[13,11,12,10,14,-1,14,-16,-8,12,-16,-13,-6,-6],
			[6,11,5,6,8,14,9,4,7,13,11,11,6,1]):
		x=z%26
		print(z)
		z//=n0
		x+=n1
		print("Target:",x)
		x = 1 if x!=d else 0
		z*=25*x+1
		if x:
			z+=(d+n2)
		print(x,z)
	return z==0

			
def main(input:str):
	p1 = 0
	p2 = 0
	print(testNum(99999999999999))
	exit(0)
	for l in range(99999999999999,9999999999999,-1):
		if(testNum(l)):
			print(l)
			exit(1)
	return (p1, p2)