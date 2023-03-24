from string import ascii_uppercase
def day19(input):
	G = {}
	pos = None
	for y, l in enumerate(input.splitlines()):
		for x, v in enumerate(l):
			if v != ' ':
				G[x+y*1j]=v
				if y == 0:pos=(x+y*1j)
	d = 1
	out = ""
	p2=0
	while True:
		p2+=1
		if G[pos] in ascii_uppercase:
			out+=G[pos]
		if pos+d not in G:
			if pos+d*1j in G:
				d*=1j
			elif pos-d*1j in G:
				d*=-1j
			else:
				break
		pos+=d
			
	return [out,p2]