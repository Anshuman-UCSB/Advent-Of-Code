def main(input):
	nums = {int(l) for l in input.splitlines()}
	p1 = None
	for n in nums:
		if 2020-n in nums:
			p1 = n*(2020-n)
			break
	
	for n1 in nums:
		for n2 in nums:
			if n1+n2>=2020:continue
			for n3 in nums:
				if n1+n2+n3 == 2020:
					return p1, n1*n2*n3