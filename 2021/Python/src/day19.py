from utils.aocUtils import *
from itertools import permutations, combinations

# def hashPoints()

def main(input:str):
	p1 = 0
	p2 = 0
	scanners = []
	for sn in [x.splitlines()[1:] for x in input.split("\n\n")]:
		scanners.append([])
		for x,y,z in [map(int,l.split(',')) for l in sn]:
			scanners[-1].append((x,y,z))
	print(rotate((1,2,3)))
	return (p1, p2)