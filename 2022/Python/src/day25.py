from utils.aocUtils import *
values = ['=','-','0','1','2']
def solve(l):
	v = 0
	for c in l:
		v = values.index(c) - 2 + v*5
	return v
def f(n):
	if n == 0: return ""
	if (m:=n%5) in (0,1,2):return f(n//5) + str(m)
	if n%5 == 3: 	return f((n+2)//5) + "="
	if n%5 == 4: 	return f((n+1)//5) + "-"
def main(input:str):
	target = 0
	p1 = f(sum(solve(l) for l in input.splitlines()))
	return (p1, None)