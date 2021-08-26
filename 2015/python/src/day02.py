from utils.aocUtils import readNums
def main(input:str) -> tuple:
	p1 = 0
	p2 = 0
	for n in [sorted(readNums(l)) for l in input.splitlines()]:
		p1+=2*(n[0]*n[1] + n[1]*n[2] + n[2]*n[0]) + n[0]*n[1]
		p2+=2*(n[0]+n[1]) + n[0]*n[1]*n[2]
	return (p1, p2)