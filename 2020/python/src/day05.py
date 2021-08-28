from utils.aocUtils import *

def evalId(instr):
	l, h = 0, 127
	for c in instr[:7]:
		m = (h+l)//2
		if c=='F': 	h=m
		else:		l=m+1
	y = l
	l, h = 0, 7
	for c in instr[7:]:
		m = (h+l)//2
		if c=='L': 	h=m
		else:		l=m+1
	return 8*y+l


def main(input:str):
	ids = [evalId(x) for x in input.splitlines()]
	p1 = max(ids)
	ids.sort()
	for i in range(len(ids)-1, -1, -1):
		if ids[i-1]+1 != ids[i]:
			p2 = ids[i]-1
			break
	return (p1, p2)