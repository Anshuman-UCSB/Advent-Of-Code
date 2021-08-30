from utils.aocUtils import *

def p1s(input):
	regs = {}
	mask = [None]*36
	for l in input.splitlines():
		if l.startswith("mask"):
			mask = [None if x =='X' else int(x) for x in l[7:]]
		else:
			loc, v = readNums(l)
			regs[loc] = masked(v, mask)
	return sum(regs.values())

def readFloating(regs, loc, val):
	if None not in loc:
		regs[bitsToInt(loc)] = val
		# print(bitsToInt(loc))
	else:
		i = loc.index(None)
		c = loc.copy()
		c[i] = 0
		readFloating(regs, c, val)
		c = loc.copy()
		c[i] = 1
		readFloating(regs, c, val)
	
def p2s(input):
	regs = {}
	mask = [None]*36
	for l in input.splitlines():
		if l.startswith("mask"):
			mask = [None if x =='X' else int(x) for x in l[7:]]
		else:
			loc, v = readNums(l)
			loc = list(map(int, list(bin(loc)[2:])))
			loc = [0]*(36-len(loc))+loc

			for i in range(36):
				if mask[i] == 1:
					loc[i] = 1
				elif mask[i] == None:
					loc[i] = None
			readFloating(regs, loc, v)
	return sum(regs.values())

def masked(val, mask):
	l = list(map(int, list(bin(val)[2:])))
	l = [0]*(36-len(l))+l
	for i in range(36):
		if mask[i] != None:
			l[i] = mask[i]
	return bitsToInt(l)
			
def bitsToInt(bits):
	return int("".join(map(str, bits)),2)

def main(input:str):
	p1 = p1s(input)
	p2 = p2s(input)
	return (p1, p2)