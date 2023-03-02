from math import gcd
def lcm(a,b):
	return a*b //gcd(a,b)

def day13(input):
	scn = {}
	for l in input.splitlines():
		d,r=map(int,l.split(": "))
		scn[d]=(r,(r-1)*2)
	p1=0
	for i in range(max(scn)+1):
		if i in scn:
			if i%scn[i][1] == 0:
				p1+=i*scn[i][0]
	p2 = 0
	while True:
		p2+=1
		for i in range(max(scn)+1):
			if i in scn:
				if (p2+i)%scn[i][1] == 0:
					break
		else:
			break
	return [p1,p2]