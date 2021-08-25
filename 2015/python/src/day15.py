from utils.aocUtils import readNums
import numpy as np

ingredients = None
def p1Eval(partitions):
	t = ingredients[:,:-1]*partitions[:,None]
	s = np.sum(t, dtype=int, axis=0)
	s[s<0] = 0
	return np.prod(s, dtype=int)
	
def p2Eval(partitions):
	if sum(ingredients[:,-1]*partitions) != 500:
		return 0
	return p1Eval(partitions)

def main(input:str) -> tuple:
	global ingredients
	ingredients = np.array([readNums(x) for x in input.splitlines()])
	p1 = 0
	p2 = 0
	for a in range(100-2):
		for b in range(100-1-a):
			for c in range(100-a-b):
				d = 100-a-b-c
				p1 = max(p1, p1Eval(np.array([a,b,c,d])))
				p2 = max(p2, p2Eval(np.array([a,b,c,d])))
	return (p1, p2)