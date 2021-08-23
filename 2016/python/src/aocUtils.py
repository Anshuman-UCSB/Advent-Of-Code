import re
def printAnswer(result : tuple):
	print("[P1]",result[0])
	print("[P2]",result[1])

def imaginaryCoordToDist(n: complex):
	return int(abs(n.real)) + int(abs(n.imag))

def readNums(inp):
	return list(map(int, re.findall(r"(-?\d+)", inp)))