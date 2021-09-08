from utils.aocUtils import *
from src.intcode import *
def main(input:str):
	c = CPU(input)
	c.regs[1] = 12
	c.regs[2] = 2
	c.run()
	p1 = c.regs[0]
	for i in range(100):
		for j in range(100):
			c = CPU(input)
			c.regs[1] = i
			c.regs[2] = j
			c.run()
			if c.regs[0] == 19690720:
				return (p1, 100*i+j)