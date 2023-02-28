def day6(input):
	banks = tuple(map(int,input.split()))
	n = len(banks)
	def iter(banks):
		best,bi=banks[0],0
		for i in range(1,n):
			if banks[i]>best:
				best=banks[i]
				bi=i
		flat = best//n
		out = list(banks)
		out[bi]=0
		for i in range(n):
			out[i]+=flat
		for j in range(best-n*flat):
			out[(bi+j+1)%n]+=1
		return tuple(out)
	seen = {}
	p1 = 0
	while banks not in seen:
		seen[banks]=p1
		p1+=1
		# print(banks)
		banks=iter(banks)
	p2=p1-seen[banks]
	return [p1,p2]