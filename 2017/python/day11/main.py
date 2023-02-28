def day11(input):
	p2=0
	step={
		'n':2j,
		'ne':1+1j,
		'se':1-1j,
		's':-2j,
		'sw':-1-1j,
		'nw':-1+1j
	}
	def dist(p):
		return int(abs(p.real)+max(abs(p.imag)-abs(p.real),0)//2)
	p=0
	for c in input.split(','):
		p+=step[c]
		p2=max(p2,dist(p))
	print(p)
	p1=dist(p)
	return [p1,p2]