def day4(input):
	def valid1(l):
		spl = l.split()
		return len(spl) == len(set(spl))
	def valid2(l):
		spl = l.split()
		return len(spl) == len(set(map(tuple,map(sorted,spl))))
	return [sum(valid1(l) for l in input.splitlines()),
			sum(valid2(l) for l in input.splitlines())]