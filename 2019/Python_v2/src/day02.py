from utils.aocUtils import *
from src.intcode import CPU


def main(input:str):
	c = CPU(input)
	c.regs[1] = 12
	c.regs[2] = 2
	c.run()
	p1 = c.regs[0]
	p2 = 0
	while True:
		c = CPU(input)
		c.regs[1] = p2//100
		c.regs[2] = p2%100
		c.run()
		if(c.regs[0] == 19690720):
			break
		p2+=1
	return (p1, p2)