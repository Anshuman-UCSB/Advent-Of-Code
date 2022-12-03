from utils.aocUtils import *
def win(a, b):
	p1 = ord(a) - ord('A')
	p2 = ord(b) - ord('X')
	if p2 == (p1 + 1)%3:
		return 6
	if (p2 + 1)%3 == p1:
		return 0
	return 3
def main(input:str):
	p1 = p2 = 0
	scores = {'X':1, 'Y':2, 'Z':3}
	result = {'A':{'X':3,'Y':6,'Z':0},'B':{'X':0,'Y':3,'Z':6},'C':{'X':6,'Y':0,'Z':3}}
	p2Map = {'X': 0, 'Y': 3, 'Z': 6}
	for l in input.splitlines():
		a, b = l.split()
		p1 += result[a][b]
		p1 += scores[b]
		
		p2 += p2Map[b]
		for k,v in result[a].items():
			if v == p2Map[b]:
				b = k
				break
		p2 += scores[b]
		
	return (p1, p2)