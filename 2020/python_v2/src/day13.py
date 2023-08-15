import re

def crt(m, x):
    while True:
        temp1 = pow(m[1],-1,m[0]) * x[0] * m[1] + \
                pow(m[0],-1,m[1]) * x[1] * m[0]
        temp2 = m[0] * m[1]

        x.remove(x[0])
        x.remove(x[0])
        x = [temp1 % temp2] + x

        m.remove(m[0])
        m.remove(m[0])
        m = [temp2] + m
 
        if len(x) == 1:
            break
 
    return x[0]

def main(input):
	earliest, *busses = map(int,re.findall(r"\d+", input))
	depart = earliest
	p1 = None
	while True:
		for b in busses:
			if depart%b == 0:
				p1 = (depart-earliest)*b
				break
		if p1:break
		depart += 1
	
	m, x = [], []
	for i,l in enumerate(input.splitlines()[1].split(',')):
		if l == 'x':continue
		x.append(-i)
		m.append(int(l))
	return p1, crt(m, x)
