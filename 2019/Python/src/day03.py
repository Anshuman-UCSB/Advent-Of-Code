from utils.aocUtils import *
def main(input:str):
	dx = {
		"R":1,
		"U":1j,
		"L":-1,
		"D":-1j
	}
	pathA,pathB = {}, {}
	p = 0
	step = 1
	for c in input.splitlines()[0].split(","):
		for _ in range(int(c[1:])):
			p+=dx[c[0]]
			pathA[p]=step
			step+=1
	
	p = 0
	step = 1
	for c in input.splitlines()[1].split(","):
		for _ in range(int(c[1:])):
			p+=dx[c[0]]
			pathB[p]=step
			step+=1
	
	intersections = set(pathA.keys()).intersection(set(pathB.keys()))
	print(intersections)

	p1 = min(map(imaginaryCoordToDist,intersections))
	p2 = min(map(lambda x: pathA[x]+pathB[x],intersections))
	return (p1, p2)