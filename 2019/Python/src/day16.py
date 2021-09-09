from utils.aocUtils import *
import numpy as np

def pattern(c, l):
	base = [0,1,0,-1]
	block = [i for i in base for _ in range(c)]
	while len(block)<=l:
		block = block+block
	return np.array(block[1:l+1])
def p1s(n):
	digits = []
	for i in range(len(n)):
		p = pattern(i+1, len(n))
		digits.append(abs(np.sum(n*p))%10)
	return digits

def p2s(input):
	shift = 0
	for d in input[:7]:
		shift = shift*10+int(d)
	n = np.array(list(map(int,list((input*10000)[shift:]))))
	for _ in range(100):
		for i in range(len(n)-2, -1, -1):
			n[i]+=n[i+1]
			n[i]%=10
	out = 0
	for v in n[:8]:
		out=out*10+v
	return out
def main(input:str):
	n = np.array(list(map(int,list(input))))
	for i in range(100):
		n = p1s(n)
	p1 = ""
	for v in n[:8]:
		p1+=str(v)
	return (p1, p2s(input))