from itertools import groupby
def hasStraight(pw):
	t = list(map(ord, pw))
	for i in range(len(t)-2):
		if t[i]+1 == t[i+1] and t[i+1]+1 == t[i+2]:
			return True
	return False

def noInvalids(pw):
	for inv in "iol":
		if inv in pw:
			return False
	return True

def twoDups(pw):
	g = groupby(pw)
	s =set([x for x,v in [(k, len(list(v))) for k, v in g] if v>1])
	return len(s)>1

def iterPw(pw):
	t = list(pw)
	alph = 'abcdefghjkmnpqrstuvwxyza'
	m = {alph[i]:alph[i+1] for i in range(23)}
	for i in range(len(t)-1,-1,-1):
		t[i] = m[t[i]]
		if t[i] != 'a':
			break
	return "".join(t)
	
			

def main(input:str) -> tuple:
	while not noInvalids(input) or not twoDups(input) or not hasStraight(input):
		input = iterPw(input)
	p1 = input
	input = iterPw(input)
	while not noInvalids(input) or not twoDups(input) or not hasStraight(input):
		input = iterPw(input)
	return (p1,input)