def day1(input):
	inp=list(map(int,input))
	n = len(inp)
	p1 = sum(inp[i] if inp[i]==inp[i-1] else 0 for i in range(n))
	p2 = sum(inp[i] if inp[i]==inp[(i+n//2)%n] else 0 for i in range(n))
	return [p1,p2]