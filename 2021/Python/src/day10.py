from utils.aocUtils import *
from statistics import median
def p2s(l):
	scores = {')':1, ']':2, '}':3, '>':4}
	s = 0
	for c in l:
		s = s*5+scores[c]
	return s

def main(input:str):
	p1 = 0
	incompletes = []
	for l in input.splitlines():
		corrupted = False
		needs = {"(":")","{":"}","<":">","[":"]"}
		scores = {')':3, ']':57,'}':1197,'>':25137}
		s = []
		for c in l:
			if c in needs:
				s.append(needs[c])
			else:
				if s.pop(-1) != c:
					p1+=scores[c]
					corrupted = True
					break
		if not corrupted:
			incompletes.append(s[::-1])
	return (p1, median([p2s(c) for c in incompletes]))