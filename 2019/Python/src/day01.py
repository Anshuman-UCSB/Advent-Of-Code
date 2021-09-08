from utils.aocUtils import *
def iter(n):
	return n//3 - 2
def main(input:str):
	p1 = sum(map(iter, map(int,input.splitlines())))
	t = list(map(int, input.splitlines()))
	p2 = 0
	while t!=[]:
		s = []
		for v in t:
			x = iter(v)
			if x>0:
				s.append(x)
		p2+=sum(s)
		t = s
	return (p1, p2)