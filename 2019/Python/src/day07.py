from utils.aocUtils import *
import itertools
from src.intcode import *

def simulate1(phases, input):
	amplifiers = []
	last = 0
	for p in phases:
		amplifiers.append(CPU(input))
		amplifiers[-1].push(p)
		amplifiers[-1].push(last)
		amplifiers[-1].run()
		last = amplifiers[-1].outputs[0]
	return last

def simulate2(phases, input):
	amplifiers = []
	for p in phases:
		amplifiers.append(CPU(input))
		amplifiers[-1].push(p)
	last = 0
	while any([not x.done for x in amplifiers]):
		for i, am in enumerate(amplifiers):
			am.push(last)
			try:
				am.run()
			except EmptyInput:
				pass
			last = am.pop()
			if i == 4:
				out = last
	return out

def main(input:str):
	p1 = p2 = 0
	for p in itertools.permutations([0,1,2,3,4]):
		p1 = max(p1, simulate1(p, input))
	for p in itertools.permutations([5,6,7,8,9]):
		p2 = max(p2, simulate2(p, input))
	return (p1, p2)


"""
3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5

do this 5 times:
	reg[27] = input * 2 + phase
	output reg[27]
"""