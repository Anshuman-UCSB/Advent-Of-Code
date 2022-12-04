from utils.aocUtils import *
def toSet(section):
	a,b = section.split("-")
	return (int(a), int(b))
def contains(A,B):
	return (A[0]<=B[0] and A[1]>=B[1]) or (B[0]<=A[0] and B[1]>=A[1])
def overlap(A,B):
	return A[0]<=B[0]<=A[1] or B[0]<=A[0]<=B[1]
def main(input:str):
	p1 = p2 = 0
	for l in input.splitlines():
		a,b = l.split(",")
		a = toSet(a)
		b = toSet(b)
		if contains(a,b):
			p1+=1
		if overlap(a,b):
			p2+=1
	return (p1, p2)