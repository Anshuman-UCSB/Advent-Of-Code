from utils.aocUtils import *
@cache
def score(l):
	return ord(l.lower()) - ord('a') + 1 + l.isupper()*26
def main(input:str):
	p1 = p2 = 0
	c = 0
	for l in input.splitlines():
		sz = len(l)//2
		shared ,= set(l[:sz])&set(l[sz:])
		p1 += score(shared)
		if c == 0:
			st = set(l)
		else:
			st &= set(l)
		if c == 2:
			sh ,= st
			p2 += score(sh)
		c =(c+1)%3
	return (p1, p2)