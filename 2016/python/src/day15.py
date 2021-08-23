from src.aocUtils import readNums
from src.aocUtils import chinese_remainder
#Disc #6 has 19 positions; at time=0, it is at position 7.

def solve(discs):
	n = []
	a = []
	for dist, period, _, pos in discs:
		n.append(period)
		a.append((-dist-pos)%period)
	return chinese_remainder(n,a)
def main(input:str) -> tuple:
	discs = []
	for l in input.splitlines():
		discs.append(readNums(l))
	p1 = solve(discs)
	discs.append((7,11,0,0))
	return (p1, solve(discs))
