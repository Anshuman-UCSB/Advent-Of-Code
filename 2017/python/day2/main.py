def day2(input):
	input = [sorted(map(int,l.split())) for l in input.splitlines()]
	p1 = sum(max(l)-min(l) for l in input)
	p2 = 0
	def p2Row(r):
		for i in range(1,len(r)):
			for j in range(i):
				if r[i]%r[j]==0:
					return r[i]//r[j]
		return float('inf')
	p2 = sum(p2Row(r) for r in input)
	# for r in input:
	# 	for i in range(1,len(r)):
	# 		for j in range(i):
	# 			if r[i]%r[j]==0:
	# 				p2+=r[i]//r[j]
	return [p1,p2]