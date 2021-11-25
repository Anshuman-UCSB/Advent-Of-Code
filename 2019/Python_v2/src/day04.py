from utils.aocUtils import *
import re

def valid(x):
	l = list(map(int, list(str(x))))
	if len(l) != 6:
		return False
	if re.match(r".*(\d)\1", str(x)) == None:
		return False
	for i in range(len(l)-1):
		if(l[i]>l[i+1]):
			return False
	return True

def valid2(x):
	l = list(map(int, list(str(x))))
	l.append(-1)
	for i in range(len(l)-1):
		if l[i] == l[i+1] and l[i] != l[i+2] and l[i] != l[i-1]:
			return True
	return False

def main(input:str):
	p1 = sum([1 for x in range(*map(int,input.split("-"))) if valid(x)])
	p2 = sum([1 for x in range(*map(int,input.split("-"))) if valid(x) and valid2(x)])
	return (p1, p2)