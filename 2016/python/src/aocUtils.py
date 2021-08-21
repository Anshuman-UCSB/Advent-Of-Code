
def printAnswer(result : tuple):
	print("[P1]",result[0])
	print("[P2]",result[1])

def imaginaryCoordToDist(n: complex):
	return int(abs(n.real)) + int(abs(n.imag))