from utils.aocUtils import *
from src.intcode import *
def isIntersection(scaffolds, p):
	dx = [1,-1,1j,-1j]
	for d in dx:
		if p+d not in scaffolds:
			return False
	return True

def p2(scaffolds, pos, input):
	dir = -1j
	path = []
	while True:
		if pos+dir in scaffolds:
			path[-1]+=1
			pos+=dir
		else:
			if pos+dir*1j in scaffolds:
				dir*=1j
				path.append("R")
				path.append(0)
			elif pos+dir*-1j in scaffolds:
				dir*=-1j
				path.append("L")
				path.append(0)
			else:
				break
	# return ",".join(map(str, path))
	instr = """A,B,A,C,A,A,C,B,C,B\nL,12,L,8,R,12\nL,10,L,8,L,12,R,12\nR,12,L,8,L,10\nn\n"""
	c = CPU(input)
	c.regs[0]=2
	for v in instr:
		c.push(ord(v))
	c.run()
	return c.outputs[-1]
	# for v in c.outputs:
	# 	print(chr(v),end="")
	
def main(input:str):
	c = CPU(input)
	c.run()
	s = ""
	for v in c.outputs:
		s+=chr(v)
	c.outputs = []
	scaffolds = set()
	for y,r in enumerate(s.splitlines()):
		for x, v in enumerate(r):
			if v=='#':
				scaffolds.add(complex(x,y))
			if v=='^':
				pos = complex(x,y)
	p1 = 0
	for p in scaffolds:
		if isIntersection(scaffolds, p):
			p1+=int(p.real*p.imag)
	return (p1, p2(scaffolds, pos, input))
