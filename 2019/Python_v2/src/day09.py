from utils.aocUtils import *
from src.intcode import *

def tests():
	cases = {
		"109, -1, 4, 1, 99": -1,
		"109, -1, 104, 1, 99" : 1,
		"109, -1, 204, 1, 99" : 109,
		"109, 1, 9, 2, 204, -6, 99" : 204,
		"109, 1, 109, 9, 204, -6, 99" : 204,
		"109, 1, 209, -1, 204, -106, 99" : 204,
		}
	for inp, out in cases.items():
		c = CPU(inp)
		c.run()
		print(inp,"->",out)
		result = c.pop()
		print(result)
		assert(out == result)


def main(input:str):
	# tests()
	# print(simulate("109, 1, 203, 2, 204, 2, 99", [1423], True))
	# return 1,1
	c = CPU(input)
	c.push(1)
	c.run()
	p1 = c.pop()
	c = CPU(input)
	c.push(2)
	c.run()
	p2 = c.pop()
	return (p1, p2)