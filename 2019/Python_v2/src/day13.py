from utils.aocUtils import *
from src.intcode import *


def main(input:str):
	c = CPU(input)
	c.run()
	p1 = c.outputQ[2::3].count(2)
	c = CPU(input)
	c.regs[0] = 2
	for i, v in enumerate(c.regs):
		if v == 3 and c.regs[i+1] == 0 and c.regs[i-1] == 0:
			t = i
			while c.regs[t] != 1:
				c.regs[t] = 3
				t+=1
			t = i
			while c.regs[t] != 1:
				c.regs[t] = 3
				t-=1
			
			break
	while not c.done:
		c.push(0)
		c.runUntilInput()
	# for i, v in enumerate(c.outputQ):
	# 	print(v)
	return (p1, c.outputQ[-1])