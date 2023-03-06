def generator(mul,start,req=0):
	n = start
	while True:
		n= (n*mul)%2147483647
		while n&req:
			n= (n*mul)%2147483647
		yield n&0xFFFF

def day15(input):
	sa,sb = map(lambda x:int(x.split()[-1]),input.splitlines())
	A,B=generator(16807,sa),generator(48271,sb)
	p1=0
	for _ in range(40_000_000):
		p1+=next(A)==next(B)
	A,B=generator(16807,sa,0b11),generator(48271,sb,0b111)
	p2=0
	for _ in range(5_000_000):
		p2+=next(A)==next(B)
	return [p1,p2]