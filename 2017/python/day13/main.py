def day13(input):
	scn = {}
	for l in input.splitlines():
		d,r=map(int,l.split())
		scn[d]=(r,(r-1)*2)
	return [None,None]