from utils.aocUtils import *
from operator import add, sub, mul, floordiv,truediv
INTEGER_DIV = True
div = floordiv if INTEGER_DIV else truediv
translation = {'+': add,'-': sub,'*': mul,'/': div}
opposite = {add:sub,sub:add,div:mul,mul:div}
class Monkey:
	def __init__(self, line):
		self.valMonkey = line[0] in "0123456789"
		if self.valMonkey:
			self.val = int(line)
		else:
			self.lhs, op, self.rhs = line.split()
			self.op = translation[op]

class Eqn:
	def __init__(self, inp):
		self.monkeys = {}
		for l in inp.splitlines():
			self.monkeys[l[:4]] = Monkey(l[6:])
		self.p2 = None
	@cache #TODO CHECK IF WORKS
	def eval(self, name):
		m = self.monkeys[name]
		if m.valMonkey:
			return m.val
		else:
			return m.op(self.eval(m.lhs),self.eval(m.rhs))
	def containHuman(self, name):
		if name == 'humn': return True
		m = self.monkeys[name]
		if m.valMonkey == True: return False
		return self.containHuman(m.lhs) or self.containHuman(m.rhs)
	def buildEq(self, name):
		if name == "humn":
			return "x"
		m = self.monkeys[name]
		rev = {v:k for k,v in translation.items()}
		if m.valMonkey:
			return str(m.val)
		else:
			return "("+self.buildEq(m.lhs) + rev[m.op] + self.buildEq(m.rhs)+")"
	def revSolve(self, name, val):
		if name == "humn":
			self.p2 = val
		else:
			m = self.monkeys[name]
			assert(m.valMonkey == False)
			if self.containHuman(m.lhs):
				rhsV = self.eval(m.rhs)
				self.revSolve(m.lhs, opposite[m.op](val, rhsV))
			elif self.containHuman(m.rhs):
				lhsV = self.eval(m.lhs)
				self.revSolve(m.rhs, opposite[m.op](val, lhsV))
			else:
				assert False, "Uh oh"

def main(input:str):
	p2 = 0
	eq = Eqn(input)
	
	m = eq.monkeys['root']
	if eq.containHuman(m.lhs):
		solveVal = eq.eval(m.rhs)
		base = m.lhs
	elif eq.containHuman(m.rhs):
		solveVal = eq.eval(m.lhs)
		base = m.rhs
	print(eq.buildEq(base),'=',solveVal)
	eq.revSolve(base, solveVal)
	return (eq.eval('root'), eq.p2) # 3087390115721 ans