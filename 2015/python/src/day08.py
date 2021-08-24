def p1Val(s):
	out = 2
	i = 1
	while i<len(s)-1:
		if s[i] == "\\":
			if s[i+1]=='x':
				out+=2
				i+=2
			out+=1
			i+=1
		i+=1
	return out

def p2Val(s):
	out = 4
	i = 1
	while i<len(s)-1:
		if s[i] in ["\\", '"']:
			out+=1
		i+=1
	return out

def main(input:str) -> tuple:
	return (sum([p1Val(s) for s in input.splitlines()]), sum([p2Val(s) for s in input.splitlines()]))