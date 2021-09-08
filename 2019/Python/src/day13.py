from utils.aocUtils import *
from src.intcode import *

def main(input:str):
	c = CPU(input)
	c.run()
	p1 = c.outputs[2::3].count(2)
	c = CPU(input)
	c.regs[0] = 2
	for i in range(1564, 1604):
		c.regs[i] = 3 #make big paddle
	while not c.done:
		try:
			c.run()
		except EmptyInput:
			c.push(0)
	p2 = c.outputs[-1]
	return (p1, p2)