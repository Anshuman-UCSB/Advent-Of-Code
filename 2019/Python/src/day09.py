from utils.aocUtils import *
from src.intcode import *

def main(input:str):
	c = CPU(input)
	c.push(1)
	c.run()
	p1 = c.pop()
	c = CPU(input)
	c.push(2)
	c.run()
	p2 = c.pop()
	return (p1, p2)