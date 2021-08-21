def isTriangle(t):
	t.sort()
	return (t[0]+t[1] > t[2])

def p1(input):
	out = 0
	for l in input.splitlines():
		t = [int(x) for x in l.split()]
		out+=isTriangle(t)
	return out

def p2(input):
	out = 0
	spl = [[int(n) for n in x.split()] for x in input.splitlines()]
	for i in range(0, len(spl), 3):
		for k in range(3):
			out+=isTriangle([spl[i][k], spl[i+1][k], spl[i+2][k]])
	return out

def main(input:str) -> tuple:
	
	return (p1(input), p2(input))
