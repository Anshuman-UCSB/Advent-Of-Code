from utils.aocUtils import *

def getPath(line):
	path = set()
	pos = 0
	dirMod = {
		"U":1j, "D":-1j,
		"R":1,	"L":-1
	}
	steps = {}
	time = 0
	for instr in line.split(","):
		for _ in range(int(instr[1:])):
			pos += dirMod[instr[0]]
			time+=1
			path.add(pos)
			steps[pos] = time
	return path, steps

def main(input:str):
	pathA, stepA = getPath(input.splitlines()[0])
	pathB, stepB = getPath(input.splitlines()[1])
	insct = pathA.intersection(pathB)
	p1 = min([imaginaryCoordToDist(x) for x in insct])
	p2 = min([stepA[p] + stepB[p] for p in insct])
	return (p1, p2)