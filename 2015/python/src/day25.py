from utils.aocUtils import readNums, modMult

def nextCode(code):
	return modMult(code, 252533, 33554393)

def main(input:str):
	target = readNums(input)
	code = 20151125
	k = target[0]-1
	n = k+target[1]
	pos = sum(range(1,n+1))-k
	for i in range(pos-1):
		code = nextCode(code)
	return (code, None)