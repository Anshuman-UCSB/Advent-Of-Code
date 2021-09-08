from utils.aocUtils import *
from src.intcode import *
def main(input:str):
	c = CPU(input)
	c.push(1)
	c.run()
	p1 = c.outputs[-1]

	c = CPU(input)
	c.push(5)
	c.run()
	p2 = c.outputs[-1]
	return (p1, p2)