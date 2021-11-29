from utils.aocUtils import *
from src.intcode import *
from itertools import permutations

class Amp:
	def __init__(self, input, phase):
		self.c = CPU(input)
		self.c.push(phase)
	
	def push(self, val):
		self.c.push(val)
	
	def run(self):
		self.c.runUntilInput()

def test(perm, input):
	boosters = [Amp(input, n) for n in perm]
	old = 0
	for i in range(5):
		boosters[i].push(old)
		boosters[i].run()
		old = boosters[i].c.pop()
	return old
def test2(perm, input):
	boosters = [Amp(input, n) for n in perm]
	old = 0
	out = -1
	while True:
		try:
			for i in range(5):
				boosters[i].push(old)
				boosters[i].run()
				old = boosters[i].c.pop()
				if i == 4:
					out = old
		except StoppedCPU:
			if boosters[4].c.done:
				break
	return out

def main(input:str):
	p1 = 0
	p2 = 0
	for p in permutations([0,1,2,3,4]):
		p1 = max(p1, test(p, input))
	for p in permutations([5,6,7,8,9]):
		p2 = max(p2, test2(p, input))
	return (p1, p2)