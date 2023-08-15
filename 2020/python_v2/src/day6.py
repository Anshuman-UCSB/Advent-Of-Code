def main(input):
	p1 = p2 = 0
	for l in input.split("\n\n"):
		p1+=len(set(l.replace('\n','')))
		all = set("abcdefghijklmnopqrstuvwxyz")
		for p in l.splitlines():
			all &= set(p)
		p2 += len(all)
	return p1,p2