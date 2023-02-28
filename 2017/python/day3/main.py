from math import ceil,sqrt
def day3(input):
	n=int(input)
	# https://oeis.org/A214526
	layer = ceil(.5*sqrt(n)-.5)
	p1 = layer + abs(((n-1)%(2*layer) - layer))
	with open("day3/A141481", 'r') as A141481:
		for l in A141481.readlines()[2:-1]:
			_,b=map(int,l.split())
			if b>n:
				p2=b
				break
	return [p1,p2]